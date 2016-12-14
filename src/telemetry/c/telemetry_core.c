#include "telemetry_core.h"
#include "framing.h"
#include "crc16.h"
#include "dictionnary.h"

static TM_state * statePtr;
static TM_transport * transportPtr;
static uint8_t incomingBuffer[INCOMING_BUFFER_SIZE];
static uint8_t outgoingBuffer[OUTGOING_BUFFER_SIZE];
static char topicBuffer[TOPIC_BUFFER_SIZE];

struct nlist * hashtab[HASHSIZE];


static void (*userCallback)(TM_state * s, TM_msg * m);

uint16_t header(TM_type type);
uint16_t topic(const char * topic, uint16_t crc);
uint16_t payload(const void * payload, uint32_t size, uint16_t crc);
void frame(const char * t, TM_type type, const void * data, uint32_t datasize);
void send(void * buf, uint32_t size);
void on_incoming_frame(uint8_t * storage, uint32_t size);
void on_incoming_error(int32_t errCode);
void emptyCallback(TM_state * s, TM_msg * m);

void init_telemetry(TM_transport * t)
{
  statePtr = NULL;
  transportPtr = t;
  userCallback = emptyCallback;

  // Setup framing
  initialize_framing();
  incoming_storage(incomingBuffer,INCOMING_BUFFER_SIZE);
  outgoing_storage(outgoingBuffer, OUTGOING_BUFFER_SIZE);
  set_on_incoming_frame(on_incoming_frame);
  set_on_incoming_error(on_incoming_error);

  // Setup update dictionnary
  init_table(hashtab);
}

void attach(const char * name, void (*callback)(TM_msg * m))
{
    install(hashtab, name, (void*)(callback), ptr_function);
}

void attach_f32(const char * name, float * variable)
{
    install(hashtab, name, (void*)(variable), ptr_f32);
}

void attach_u8(const char * name, uint8_t * variable)
{
    install(hashtab, name, (void*)(variable), ptr_u8);
}

void attach_u16(const char * name, uint16_t * variable)
{
    install(hashtab, name, (void*)(variable), ptr_u16);
}

void attach_u32(const char * name, uint32_t * variable)
{
    install(hashtab, name, (void*)(variable), ptr_u32);
}

void attach_i8(const char * name, int8_t * variable)
{
    install(hashtab, name, (void*)(variable), ptr_i8);
}

void attach_i16(const char * name, int16_t * variable)
{
    install(hashtab, name, (void*)(variable), ptr_i16);
}

void attach_i32(const char * name, int32_t * variable)
{
    install(hashtab, name, (void*)(variable), ptr_i32);
}

void publish(const char * t, const char * msg)
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

void subscribe(void (*callback)(TM_state* s, TM_msg* m), TM_state * s)
{
  statePtr = s;
  userCallback = callback;
}

void update_telemetry()
{
  // If user forgot to define transport by calling init_telemetry, abort
  if(!transportPtr)
    return;

  uint32_t amount = transportPtr->readable();
  uint32_t i = 0 ;
  for(i = 0 ; i < amount ; i++)
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
  uint32_t i = 0 ;
  for(i = 0 ; i < strlen(t) ; i++)
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
  uint32_t i = 0 ;
  for(i = 0 ; i < size ; i++)
  {
    append(ptr[i]);
    crc = crc16_recursive(ptr[i], crc);
  }
  return crc;
}

void frame(const char * t, TM_type type, const void * data, uint32_t datasize)
{
  // start new frame
  begin_frame();

  // header
  uint16_t crc = header(type);

  // topic
  crc = topic(t, crc);

  // payload
  crc = payload(data, datasize, crc);

  // crc
  append2(crc);

  // complete frame
  uint32_t bytesAmount = end_frame();

  // send data
  send(outgoingBuffer, bytesAmount);
}

void send(void * buf, uint32_t size)
{
  // If user forgot to define transport by calling init_telemetry, abort
  if(!transportPtr)
    return;

  if(transportPtr->writeable() && size > 0)
  {
    transportPtr->write(outgoingBuffer, size);
  }
}

void try_update_hashtable(TM_msg * msg)
{
  struct nlist * np = lookup(hashtab, msg->topic);

  // Topic not found
  if(np == NULL)
    return;

  switch(msg->type)
  {
      case TM_float32:
        // If hashtable has an entry of type float 32 under received topic
        if (np->ptr_f32 == NULL)
          break;
        emplace_f32(msg, np->ptr_f32);
        break;
      case TM_uint8:
        // If hashtable has an entry of type float 32 under received topic
        if (np->ptr_u8 == NULL)
          break;
        emplace_u8(msg, np->ptr_u8);
        break;
      case TM_uint16:
        // If hashtable has an entry of type float 32 under received topic
        if (np->ptr_u16 == NULL)
          break;
        emplace_u16(msg, np->ptr_u16);
        break;
      case TM_uint32:
        // If hashtable has an entry of type float 32 under received topic
        if (np->ptr_u32 == NULL)
          break;
        emplace_u32(msg, np->ptr_u32);
        break;
      case TM_int8:
        // If hashtable has an entry of type float 32 under received topic
        if (np->ptr_i8 == NULL)
          break;
        emplace_i8(msg, np->ptr_i8);
        break;
      case TM_int16:
        // If hashtable has an entry of type float 32 under received topic
        if (np->ptr_i16 == NULL)
          break;
        emplace_i16(msg, np->ptr_i16);
        break;
      case TM_int32:
        // If hashtable has an entry of type float 32 under received topic
        if (np->ptr_i32 == NULL)
          break;
        emplace_i32(msg, np->ptr_i32);
        break;
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
  char * t = (char*)(storage);
  strcpy(topicBuffer, t + 2);

  // ptr to beginning of payload
  ptr = (uint8_t*)(storage) + (uint32_t)(2 + topicSize + 1);

  TM_msg packet;
  packet.topic = topicBuffer;
  packet.type = (TM_type)head;
  packet.buffer = (void *)(ptr);
  packet.size = (uint32_t)payloadSize;

  // Try update variable if found in hash table
  try_update_hashtable(&packet);

  // Call global handler
  userCallback(statePtr,&packet);
}

void on_incoming_error(int32_t errCode)
{
  // TODO : Error management
}

void emptyCallback(TM_state * s, TM_msg * m)
{
  // Called only if the user forgot to subscribe a callback
}
