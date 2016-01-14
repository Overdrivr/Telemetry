#include "telemetry.h"
#include "framing.h"
#include "crc16.h"
#include "string.h"

static TM_state * statePtr;
static TM_transport * transportPtr;
static uint8_t incomingBuffer[INCOMING_BUFFER_SIZE];
static uint8_t outgoingBuffer[OUTGOING_BUFFER_SIZE];

static void (*userCallback)(TM_state * s, TM_msg * m);

uint16_t header(TM_type type);
uint16_t topic(const char * topic, uint16_t crc);
uint16_t payload(const void * payload, uint32_t size, uint16_t crc);
void frame(const char * t, TM_type type, const void * data, uint32_t datasize);
void send(void * buf, uint32_t size);
void on_incoming_frame(uint8_t * storage, uint32_t size);
void on_incoming_error(int32_t errCode);
void emptyCallback(TM_state * s, TM_msg * m);

void init_telemetry(TM_state* s, TM_transport * t)
{
  statePtr = s;
  transportPtr = t;
  userCallback = emptyCallback;

  // Setup framing
  initialize_framing();
  incoming_storage(incomingBuffer,INCOMING_BUFFER_SIZE);
  outgoing_storage(outgoingBuffer, OUTGOING_BUFFER_SIZE);
  set_on_incoming_frame(on_incoming_frame);
  set_on_incoming_error(on_incoming_error);
}

uint32_t emplace(TM_msg* m, char * buf, size_t bufSize)
{
  if(m->type != TM_string)
    return 0;

  uint32_t size = m->size;

  if(bufSize - 1 < size)
    size = bufSize - 1;

  strncpy(buf, (char*)(m->buffer), size);
  buf[size] = '\0';

  return 1;
}

uint32_t emplace_u8(TM_msg* m, uint8_t* dst)
{
  if(m->type != TM_uint8)
    return 0;

  *dst = *(uint8_t*)(m->buffer);
  return 1;
}

uint32_t emplace_u16(TM_msg* m, uint16_t* dst)
{
  if(m->type != TM_uint16)
    return 0;

  *dst = *(uint16_t*)(m->buffer);
  return 1;
}

uint32_t emplace_u32(TM_msg* m, uint32_t* dst)
{
  if(m->type != TM_uint32)
    return 0;

  *dst = *(uint32_t*)(m->buffer);
  return 1;
}

uint32_t emplace_i8(TM_msg* m, int8_t* dst)
{
  if(m->type != TM_int8)
    return 0;

  *dst = *(int8_t*)(m->buffer);
  return 1;
}

uint32_t emplace_i16(TM_msg* m, int16_t* dst)
{
  if(m->type != TM_int16)
    return 0;

  *dst = *(int16_t*)(m->buffer);
  return 1;
}

uint32_t emplace_i32(TM_msg* m, int32_t* dst)
{
  if(m->type != TM_int32)
    return 0;

  *dst = *(int32_t*)(m->buffer);
  return 1;
}

uint32_t emplace_f32(TM_msg* m, float* dst)
{
  if(m->type != TM_float32)
    return 0;

  *dst = *(float*)(m->buffer);
  return 1;
}

void publish(const char * t, char * msg)
{
  frame(t,TM_string,msg,strlen(msg));
}

void publish_u8(const char * t, uint8_t  msg)
{
  void * ptr = (void *)(&msg);
  frame(t,TM_uint8,ptr,1);
}

void publish_u16(const char * t, uint16_t msg)
{
  void * ptr = (void *)(&msg);
  frame(t,TM_uint16,ptr,2);
}

void publish_u32(const char * t, uint32_t msg)
{
  void * ptr = (void *)(&msg);
  frame(t,TM_uint32,ptr,4);
}

void publish_i8(const char * t, int8_t   msg)
{
  void * ptr = (void *)(&msg);
  frame(t,TM_int8,ptr,1);
}

void publish_i16(const char * t, int16_t  msg)
{
  void * ptr = (void *)(&msg);
  frame(t,TM_int16,ptr,2);
}

void publish_i32(const char * t, int32_t  msg)
{
  void * ptr = (void *)(&msg);
  frame(t,TM_int32,ptr,4);
}

void publish_f32(const char * t, float    msg)
{
  void * ptr = (void *)(&msg);
  frame(t,TM_float32,ptr,4);
}

void subscribe(void (*callback)(TM_state* s, TM_msg* m))
{
  userCallback = callback;
}

void update_telemetry(float elapsedTime)
{
  uint32_t amount = transportPtr->readable();
  for(uint32_t i = 0 ; i < amount ; i++)
  {
    uint8_t c;
    transportPtr->read(&c,1);
    feed(c);
  }
}

uint16_t header(TM_type type)
{
  // header data
  uint16_t h = type;
  uint8_t * ptr = (uint8_t*)(&h);

  // add data to frame
  append2(h);

  // compute crc and return it
  return crc16(ptr, 2);
}

uint16_t topic(const char * t, uint16_t crc)
{
  const uint8_t * ptr = (uint8_t*)t;
  for(uint32_t i = 0 ; i < strlen(t) ; i++)
  {
    // TODO : Replace with Huffman compression
    append(ptr[i]);
    crc = crc16_recursive(ptr[i], crc);
  }
  // Add NULL character
  append(0);
  return crc16_recursive(0,crc);
}

uint16_t payload(const void * p, uint32_t size, uint16_t crc)
{
  const uint8_t * ptr = (uint8_t*)p;
  for(uint32_t i = 0 ; i < size ; i++)
  {
    append(ptr[i]);
    crc = crc16_recursive(ptr[i], crc);
  }
  return crc;
}

void frame(const char * t, TM_type type, const void * data, uint32_t datasize)
{
  // start new frame
  begin();

  // header
  uint16_t crc = header(type);

  // topic
  crc = topic(t, crc);

  // payload
  crc = payload(data, datasize, crc);

  // crc
  append2(crc);

  // complete frame
  uint32_t bytesAmount = end();

  // send data
  send(outgoingBuffer, bytesAmount);
}

void send(void * buf, uint32_t size)
{
  if(transportPtr->writeable() && size > 0)
  {
    transportPtr->write(outgoingBuffer, size);
  }
}

void on_incoming_frame(uint8_t * storage, uint32_t size)
{
  if(size < 2)
    return;
  // Read header
  uint16_t head;
  uint8_t * ptr;
  ptr = (uint8_t*)(&head);
  memcpy(ptr,storage,2);

  // Read topic
  uint32_t cursor = 2;
  uint32_t topicSize = 0;
  while(cursor < size)
  {
    if(storage[cursor] == 0)
      break;
    topicSize++;
    cursor++;
  }

  if(topicSize == 0)
    return;

  // payload = total - header - topic - /0 - crc
  int32_t payloadSize = size - 2 - topicSize - 1 - 2;

  if(payloadSize <= 0)
    return;

  // Check crc
  uint16_t expected_crc = crc16(storage, size-2);
  uint16_t rcv_crc;
  ptr = (uint8_t*)(&rcv_crc);
  memcpy(ptr,storage+size-2,2);

  if(expected_crc != rcv_crc)
    return;

  // Store topic
  char * t = (char *) malloc(topicSize + 1);

  if(t == NULL)
    return;

  ptr = (uint8_t*)(storage);
  strcpy(t, ptr + 2);

  TM_msg packet;
  packet.topic = t;
  packet.type = head;
  packet.buffer = storage + 2 + topicSize + 1;
  packet.size = (uint32_t)payloadSize;

  // Call callback
  userCallback(statePtr,&packet);

  //
  free(t);
}

void on_incoming_error(int32_t errCode)
{
  // TODO : Error management
}

void emptyCallback(TM_state * s, TM_msg * m)
{
  // Called only if the user forgot to subscribe a callback
}
