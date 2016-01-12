#include "telemetry.h"
#include "framing.h"
#include "crc16.h"
#include "string.h"

static TM_state * statePtr;
static TM_transport * transportPtr;
static uint8_t incomingBuffer[INCOMING_BUFFER_SIZE];
static uint8_t outgoingBuffer[OUTGOING_BUFFER_SIZE];

uint16_t header(TM_type type);
uint16_t topic(const char * topic, uint16_t crc);
uint16_t payload(const void * payload, uint32_t size, uint16_t crc);
void send(void * buf, uint32_t size);

void init_telemetry(TM_state* s, TM_transport * t)
{
  statePtr = s;
  transportPtr = t;
  initialize_framing();
  incoming_storage(incomingBuffer,INCOMING_BUFFER_SIZE);
  outgoing_storage(outgoingBuffer, OUTGOING_BUFFER_SIZE);
}

uint32_t emplace(TM_msg* m, char * buf, size_t bufSize)
{
  if(m->type != TM_string)
    return 1;

  uint32_t size = m->size;

  if(bufSize - 1 < size)
    size = bufSize - 1;

  strncpy(buf, (char*)(m->buffer), size);
  buf[size] = '\0';

  return 0;
}

uint32_t emplace_u8(TM_msg* m, uint8_t* dst)
{
  if(m->type != TM_uint8)
    return 1;

  *dst = *(uint8_t*)(m->buffer);
  return 0;
}

uint32_t emplace_u16(TM_msg* m, uint16_t* dst)
{
  if(m->type != TM_uint16)
    return 1;

  *dst = *(uint16_t*)(m->buffer);
  return 0;
}

uint32_t emplace_u32(TM_msg* m, uint32_t* dst)
{
  if(m->type != TM_uint32)
    return 1;

  *dst = *(uint32_t*)(m->buffer);
  return 0;
}

uint32_t emplace_i8(TM_msg* m, int8_t* dst)
{
  if(m->type != TM_int8)
    return 1;

  *dst = *(int8_t*)(m->buffer);
  return 0;
}

uint32_t emplace_i16(TM_msg* m, int16_t* dst)
{
  if(m->type != TM_int16)
    return 1;

  *dst = *(int16_t*)(m->buffer);
  return 0;
}

uint32_t emplace_i32(TM_msg* m, int32_t* dst)
{
  if(m->type != TM_int32)
    return 1;

  *dst = *(int32_t*)(m->buffer);
  return 0;
}

uint32_t emplace_f32(TM_msg* m, float* dst)
{
  if(m->type != TM_float32)
    return 1;

  *dst = *(float*)(m->buffer);
  return 0;
}

void publish(const char * t, char * msg)
{
  // start new frame
  begin();

  // header
  uint16_t crc = header(TM_string);

  // topic
  crc = topic(t, crc);

  // payload
  crc = payload(msg, strlen(msg), crc);

  // crc
  append2(crc);

  // complete frame
  uint32_t bytesAmount = end();

  // send data
  send(outgoingBuffer, bytesAmount);
}

void publish_u8(const char * t, uint8_t  msg)
{

}

void publish_u16(const char * t, uint16_t msg)
{

}

void publish_u32(const char * t, uint32_t msg)
{

}

void publish_i8(const char * t, int8_t   msg)
{

}

void publish_i16(const char * t, int16_t  msg)
{

}

void publish_i32(const char * t, int32_t  msg)
{

}

void publish_f32(const char * t, float    msg)
{

}

void subscribe(char * t, void (*callback)(TM_state* s, TM_msg* m))
{

}

void update_telemetry(float elapsedTime)
{

}

uint16_t header(TM_type type)
{
  // header data
  uint16_t h = type;
  uint8_t * ptr = (uint8_t*)(&h);

  // add data to frame
  append(h);

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
  return crc;
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

void send(void * buf, uint32_t size)
{
  if(transportPtr->writeable() && size > 0)
  {
    transportPtr->write(outgoingBuffer, size);
  }
}
