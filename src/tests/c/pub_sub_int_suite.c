#include "test.h"

/// Mock of transport (serial). write is piped back to read
static uint8_t endBuffer[OUTGOING_BUFFER_SIZE];
static uint32_t sizeWritten;
static uint32_t sizeRead;

int32_t read_int(void * buf, uint32_t sizeToRead)
{
  uint8_t * ptr = (uint8_t*)buf;
  int32_t rem = sizeWritten - sizeRead;
  uint16_t range = sizeToRead > rem ? rem : sizeToRead;
  int32_t i;
  for(i = 0 ; i < range ; i++)
  {
    ptr[i] = endBuffer[sizeRead + i];
    sizeRead++;
  }

}

int32_t readable_int()
{
  return sizeWritten;
}

int32_t write_int(void * buf, uint32_t sizeToWrite)
{
  sizeWritten = sizeToWrite;
  uint8_t * ptr = (uint8_t*)buf;
  int32_t i;
  for(i = 0 ; i < sizeToWrite ; i++)
  {
    endBuffer[i] = ptr[i];
  }
}

int32_t writeable_int()
{
  return 1;
}

/// end of mock

struct TM_state {
  uint8_t called;
  char rcvTopic[OUTGOING_BUFFER_SIZE];
  int8_t rcvInt8;
  int16_t rcvInt16;
  int32_t rcvInt32;
};

void callback_int(TM_state* s, TM_msg* m)
{
  s->called = 1;
  int8_t i8 = 0;
  int16_t i16 = 0;
  int32_t i32 = 0;
  strcpy(s->rcvTopic,m->topic);

  if(emplace_i8(m,&i8))
  {
    s->rcvInt8 = i8;
  }
  if(emplace_i16(m,&i16))
  {
    s->rcvInt16 = i16;
  }
  if(emplace_i32(m,&i32))
  {
    s->rcvInt32 = i32;
  }
}

TEST publish_int8()
{
  TM_state state;
  uint16_t i;
  for(i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
  {
    endBuffer[i] = 0;
    state.rcvTopic[i] = 0;
  }
  sizeWritten = 0;
  sizeRead = 0;
  state.rcvInt8 = 0;
  state.called = 0;

  TM_transport transport;
  transport.read = read_int;
  transport.write = write_int;
  transport.readable = readable_int;
  transport.writeable = writeable_int;

  char topic[] = "topic";
  int8_t value = 127;

  init_telemetry(&transport);

  subscribe(callback_int,&state);

  publish_i8(topic, value);

  update_telemetry(0);

  ASSERT_EQ(state.called, 1);
  ASSERT_STR_EQ(topic,state.rcvTopic);
  ASSERT_EQ_FMT(value,state.rcvInt8,"%d");

  PASS();
}

TEST publish_int8_neg()
{
  TM_state state;
  uint16_t i;
  for(i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
  {
    endBuffer[i] = 0;
    state.rcvTopic[i] = 0;
  }
  sizeWritten = 0;
  sizeRead = 0;
  state.rcvInt8 = 0;
  state.called = 0;

  TM_transport transport;
  transport.read = read_int;
  transport.write = write_int;
  transport.readable = readable_int;
  transport.writeable = writeable_int;

  char topic[] = "topic";
  int8_t value = -127;

  init_telemetry(&transport);

  subscribe(callback_int,&state);

  publish_i8(topic, value);

  update_telemetry(0);

  ASSERT_EQ(state.called, 1);
  ASSERT_STR_EQ(topic,state.rcvTopic);
  ASSERT_EQ_FMT(value,state.rcvInt8,"%d");

  PASS();
}

TEST publish_int16()
{
  TM_state state;
  uint16_t i;
  for(i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
  {
    endBuffer[i] = 0;
    state.rcvTopic[i] = 0;
  }
  sizeWritten = 0;
  sizeRead = 0;
  state.rcvInt16 = 0;
  state.called = 0;

  TM_transport transport;
  transport.read = read_int;
  transport.write = write_int;
  transport.readable = readable_int;
  transport.writeable = writeable_int;

  char topic[] = "topic";
  int16_t value = 32767;

  init_telemetry(&transport);

  subscribe(callback_int,&state);

  publish_i16(topic, value);

  update_telemetry(0);

  ASSERT_EQ(state.called, 1);
  ASSERT_STR_EQ(topic,state.rcvTopic);
  ASSERT_EQ_FMT(value,state.rcvInt16,"%d");

  PASS();
}

TEST publish_int16_neg()
{
  TM_state state;
  uint16_t i;
  for(i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
  {
    endBuffer[i] = 0;
    state.rcvTopic[i] = 0;
  }
  sizeWritten = 0;
  sizeRead = 0;
  state.rcvInt16 = 0;
  state.called = 0;

  TM_transport transport;
  transport.read = read_int;
  transport.write = write_int;
  transport.readable = readable_int;
  transport.writeable = writeable_int;

  char topic[] = "topic";
  int16_t value = -32767;

  init_telemetry(&transport);

  subscribe(callback_int,&state);

  publish_i16(topic, value);

  update_telemetry(0);

  ASSERT_EQ(state.called, 1);
  ASSERT_STR_EQ(topic,state.rcvTopic);
  ASSERT_EQ_FMT(value,state.rcvInt16,"%d");

  PASS();
}

TEST publish_int32()
{
  TM_state state;
  uint16_t i;
  for(i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
  {
    endBuffer[i] = 0;
    state.rcvTopic[i] = 0;
  }
  sizeWritten = 0;
  sizeRead = 0;
  state.rcvInt32 = 0;
  state.called = 0;

  TM_transport transport;
  transport.read = read_int;
  transport.write = write_int;
  transport.readable = readable_int;
  transport.writeable = writeable_int;

  char topic[] = " topic ";
  int32_t value = 2147483647;

  init_telemetry(&transport);

  subscribe(callback_int,&state);

  publish_i32(topic, value);

  update_telemetry(0);

  ASSERT_EQ(state.called, 1);
  ASSERT_STR_EQ(topic,state.rcvTopic);
  ASSERT_EQ_FMT(value,state.rcvInt32,"%d");

  PASS();
}

TEST publish_int32_neg()
{
  TM_state state;
  uint16_t i;
  for(i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
  {
    endBuffer[i] = 0;
    state.rcvTopic[i] = 0;
  }
  sizeWritten = 0;
  sizeRead = 0;
  state.rcvInt32 = 0;
  state.called = 0;

  TM_transport transport;
  transport.read = read_int;
  transport.write = write_int;
  transport.readable = readable_int;
  transport.writeable = writeable_int;

  char topic[] = "topic";
  int32_t value = -2147483647;

  init_telemetry(&transport);

  subscribe(callback_int,&state);

  publish_i32(topic, value);

  update_telemetry(0);

  ASSERT_EQ(state.called, 1);
  ASSERT_STR_EQ(topic,state.rcvTopic);
  ASSERT_EQ_FMT(value,state.rcvInt32,"%d");

  PASS();
}

SUITE(pub_sub_int_suite) {
  RUN_TEST(publish_int8);
  RUN_TEST(publish_int8_neg);
  RUN_TEST(publish_int16);
  RUN_TEST(publish_int16_neg);
  RUN_TEST(publish_int32);
  RUN_TEST(publish_int32_neg);
}
