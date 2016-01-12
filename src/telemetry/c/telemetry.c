#include "telemetry.h"
#include "string.h"

static TM_state * statePtr;
static TM_transport * transportPtr;
static incomingBuffer[INCOMING_BUFFER_SIZE];
static outgoingBuffer[OUTGOING_BUFFER_SIZE];

uint16_t header(TM_type type);
uint16_t topic(char * topic, uint16_t crc);
uint16_t payload(void * payload, uint32_t size);
void send(void * buf, uint32_t size);

void init_telemetry(TM_state* s, TM_transport * t)
{
  statePtr = s;
  transportPtr = t;
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

void publish(const char * topic, char * msg)
{
  // start new frame
  begin();
  // header
  uint16_t crc = header(TM_string);

  // topic
  crc = topic(topic, crc);

  // payload
  crc = payload(msg, crc);

  // crc
  append2(crc);

  // complete frame
  uint32_t bytesAmount = end();

  // send data
  send(outgoingBuffer, bytesAmount);
}

void publish_u8(const char * topic, uint8_t  msg)
{

}

void publish_u16(const char * topic, uint16_t msg)
{

}

void publish_u32(const char * topic, uint32_t msg)
{

}

void publish_i8(const char * topic, int8_t   msg)
{

}

void publish_i16(const char * topic, int16_t  msg)
{

}

void publish_i32(const char * topic, int32_t  msg)
{

}

void publish_f32(const char * topic, float    msg)
{

}

void subscribe(char * topic, void (*callback)(TM_state* s, TM_msg* m))
{

}

void update_telemetry(float elapsedTime)
{

}

uint16_t header(TM_type type)
{
  // header data
  uint16_t header = type;
  // add data to frame
  append2(header);
  // compute crc and return it
  return crc16((uint8_t*)header, 2);
}

uint16_t topic(char * topic, uint16_t crc)
{
  for(uint16_t i = 0 ; i < strlen(topic) ; i++)
  {
    // TODO : Replace with Huffman compression
    append((uint8_t)topic[i]);
    crc = crc16_recursive((uint8_t)topic[i], crc);
  }
  return crc;
}

uint16_t payload(void * payload, uint32_t size)
{
  for(uint16_t i = 0 ; i < strlen(topic) ; i++)
  {
    append((uint8_t)payload[i]);
    crc = crc16_recursive((uint8_t)payload[i], crc);
  }
  return crc;
}

void send(void * buf, uint32_t size)
{
  if(transportPtr->writeable() && bytesAmount > 0)
  {
    transportPtr->write(outgoingBuffer, bytesAmount);
  }
}
