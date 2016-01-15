#include "test.h"
#include "telemetry.h"

/// Mock of transport (serial). write is piped back to read
static uint8_t endBuffer[OUTGOING_BUFFER_SIZE];
static uint32_t sizeWritten;
static uint32_t sizeRead;

int32_t read_uint(void * buf, uint32_t sizeToRead)
{
  uint8_t * ptr = (uint8_t*)buf;
  int32_t rem = sizeWritten - sizeRead;
  uint16_t range = sizeToRead > rem ? rem : sizeToRead;
  for(uint32_t i = 0 ; i < range ; i++)
  {
    ptr[i] = endBuffer[sizeRead + i];
    sizeRead++;
  }

}

int32_t readable_uint()
{
  return sizeWritten;
}

int32_t write_uint(void * buf, uint32_t sizeToWrite)
{
  sizeWritten = sizeToWrite;
  uint8_t * ptr = (uint8_t*)buf;
  for(uint32_t i = 0 ; i < sizeToWrite ; i++)
  {
    endBuffer[i] = ptr[i];
  }
}

int32_t writeable_uint()
{
  return 1;
}

/// end of mock

struct TM_state {
  uint8_t called;
  char rcvTopic[OUTGOING_BUFFER_SIZE];
  uint8_t rcvUint8;
  uint16_t rcvUint16;
  uint32_t rcvUint32;
};

void callback_uint(TM_state* s, TM_msg* m)
{
  s->called = 1;
  uint8_t u8 = 0;
  uint16_t u16 = 0;
  uint32_t u32 = 0;
  strcpy(s->rcvTopic,m->topic);
  if(emplace_u8(m,&u8))
  {
    s->rcvUint8 = u8;
  }
  if(emplace_u16(m,&u16))
  {
    s->rcvUint16 = u16;
  }
  if(emplace_u32(m,&u32))
  {
    s->rcvUint32 = u32;
  }
}

TEST publish_uint8()
{
  TM_state state;

  for(uint16_t i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
  {
    endBuffer[i] = 0;
    state.rcvTopic[i] = 0;
  }
  sizeWritten = 0;
  sizeRead = 0;
  state.rcvUint8 = 0;
  state.called = 0;

  TM_transport transport;
  transport.read = read_uint;
  transport.write = write_uint;
  transport.readable = readable_uint;
  transport.writeable = writeable_uint;

  char topic[] = "topic";
  uint8_t value = 255;

  init_telemetry(&state,&transport);

  subscribe(callback_uint);

  publish_u8(topic, value);

  update_telemetry(0);

  ASSERT_EQ(state.called, 1);
  ASSERT_STR_EQ(topic,state.rcvTopic);
  ASSERT_EQ_FMT(value,state.rcvUint8,"%d");

  PASS();
}

TEST publish_uint16()
{
  TM_state state;

  for(uint16_t i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
  {
    endBuffer[i] = 0;
    state.rcvTopic[i] = 0;
  }
  sizeWritten = 0;
  sizeRead = 0;
  state.rcvUint16 = 0;
  state.called = 0;

  TM_transport transport;
  transport.read = read_uint;
  transport.write = write_uint;
  transport.readable = readable_uint;
  transport.writeable = writeable_uint;

  char topic[] = "topic";
  uint16_t value = 65535;

  init_telemetry(&state,&transport);

  subscribe(callback_uint);

  publish_u16(topic, value);

  update_telemetry(0);

  ASSERT_EQ(state.called, 1);
  ASSERT_STR_EQ(topic,state.rcvTopic);
  ASSERT_EQ_FMT(value,state.rcvUint16,"%d");

  PASS();
}

TEST publish_uint32()
{
  TM_state state;

  for(uint16_t i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
  {
    endBuffer[i] = 0;
    state.rcvTopic[i] = 0;
  }
  sizeWritten = 0;
  sizeRead = 0;
  state.rcvUint32 = 0;
  state.called = 0;

  TM_transport transport;
  transport.read = read_uint;
  transport.write = write_uint;
  transport.readable = readable_uint;
  transport.writeable = writeable_uint;

  char topic[] = "topic";
  uint32_t value = 4294967295;

  init_telemetry(&state,&transport);

  subscribe(callback_uint);

  publish_u32(topic, value);

  update_telemetry(0);

  ASSERT_EQ(state.called, 1);
  ASSERT_STR_EQ(topic,state.rcvTopic);
  ASSERT_EQ_FMT(value,state.rcvUint32,"%d");

  PASS();
}

SUITE(pub_sub_uint_suite) {
  RUN_TEST(publish_uint8);
  RUN_TEST(publish_uint16);
  RUN_TEST(publish_uint32);
}
