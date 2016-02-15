#include "test.h"
#include "telemetry.h"

/// Mock of transport (serial). write is piped back to read
static uint8_t endBuffer[OUTGOING_BUFFER_SIZE];
static uint32_t sizeWritten;
static uint32_t sizeRead;

int32_t read_str(void * buf, uint32_t sizeToRead)
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

int32_t readable_str()
{
  return sizeWritten;
}

int32_t write_str(void * buf, uint32_t sizeToWrite)
{
  sizeWritten = sizeToWrite;
  uint8_t * ptr = (uint8_t*)buf;
  for(uint32_t i = 0 ; i < sizeToWrite ; i++)
  {
    endBuffer[i] = ptr[i];
  }
}

int32_t writeable_str()
{
  return 1;
}

/// end of mock

struct TM_state {
  uint8_t called;
  char rcvString[OUTGOING_BUFFER_SIZE];
  char rcvTopic[OUTGOING_BUFFER_SIZE];
};

void callback_str(TM_state* s, TM_msg* m)
{
  s->called = 1;
  char str[OUTGOING_BUFFER_SIZE] = {0};
  if(emplace(m,str,OUTGOING_BUFFER_SIZE))
  {
    strcpy(s->rcvString,str);
    strcpy(s->rcvTopic,m->topic);
  }
}

TEST publish_string()
{
  TM_state state;

  for(uint16_t i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
  {
    endBuffer[i] = 0;
    state.rcvTopic[i] = 0;
    state.rcvString[i] = 0;
  }
  sizeWritten = 0;
  sizeRead = 0;
  state.called = 0;

  TM_transport transport;
  transport.read = read_str;
  transport.write = write_str;
  transport.readable = readable_str;
  transport.writeable = writeable_str;

  char topic[] = "topic";
  char message[] = "someMessage";

  init_telemetry(&transport);
  set_state(&state);

  subscribe(callback_str);

  publish(topic, message);

  update_telemetry(0);

  ASSERT_EQ(state.called, 1);
  ASSERT_STR_EQ(message,state.rcvString);
  ASSERT_STR_EQ(topic,state.rcvTopic);

  PASS();
}

SUITE(pub_sub_string_suite) {
  RUN_TEST(publish_string);
}
