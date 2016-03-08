#include "test.h"

/// Mock of transport (serial). write is piped back to read
static uint8_t endBuffer[OUTGOING_BUFFER_SIZE];
static uint32_t sizeWritten;
static uint32_t sizeRead;

int32_t read_float(void * buf, uint32_t sizeToRead)
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

int32_t readable_float()
{
  return sizeWritten;
}

int32_t write_float(void * buf, uint32_t sizeToWrite)
{
  sizeWritten = sizeToWrite;
  uint8_t * ptr = (uint8_t*)buf;
  for(uint32_t i = 0 ; i < sizeToWrite ; i++)
  {
    endBuffer[i] = ptr[i];
  }
}

int32_t writeable_float()
{
  return 1;
}

/// end of mock

struct TM_state {
  uint8_t called;
  char rcvTopic[OUTGOING_BUFFER_SIZE];
  float rcvFloat;
};

void callback_float(TM_state* s, TM_msg* m)
{
  s->called = 1;
  float f32 = 0;
  strcpy(s->rcvTopic,m->topic);
  if(emplace_f32(m,&f32))
  {
    s->rcvFloat = f32;
  }
}

TEST publish_float()
{
  TM_state state;

  for(uint16_t i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
  {
    endBuffer[i] = 0;
    state.rcvTopic[i] = 0;
  }
  sizeWritten = 0;
  sizeRead = 0;
  state.rcvFloat = 0;
  state.called = 0;

  TM_transport transport;
  transport.read = read_float;
  transport.write = write_float;
  transport.readable = readable_float;
  transport.writeable = writeable_float;

  char topic[] = "topic";
  float value = 1.23E4;

  init_telemetry(&transport);

  subscribe(callback_float,&state);

  publish_f32(topic, value);

  update_telemetry(0);

  ASSERT_EQ(state.called, 1);
  ASSERT_STR_EQ(topic,state.rcvTopic);
  ASSERT_EQ_FMT(value,state.rcvFloat,"%f");

  PASS();
}

TEST publish_float_neg()
{
  TM_state state;

  for(uint16_t i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
  {
    endBuffer[i] = 0;
    state.rcvTopic[i] = 0;
  }
  sizeWritten = 0;
  sizeRead = 0;
  state.rcvFloat = 0;
  state.called = 0;

  TM_transport transport;
  transport.read = read_float;
  transport.write = write_float;
  transport.readable = readable_float;
  transport.writeable = writeable_float;

  char topic[] = "topic";
  float value = -1.23E4;

  init_telemetry(&transport);

  subscribe(callback_float,&state);

  publish_f32(topic, value);

  update_telemetry(0);

  ASSERT_EQ(state.called, 1);
  ASSERT_STR_EQ(topic,state.rcvTopic);
  ASSERT_EQ_FMT(value,state.rcvFloat,"%f");

  PASS();
}

SUITE(pub_sub_float_suite) {
  RUN_TEST(publish_float);
  RUN_TEST(publish_float_neg);
}
