#include "test.h"
#include "telemetry.h"

/// Mock of transport (serial). write is piped back to read
static uint8_t endBuffer[OUTGOING_BUFFER_SIZE];
static uint32_t sizeWritten;

int32_t read2(void * buf, uint32_t sizeToRead)
{
  uint8_t * ptr = (uint8_t*)buf;
  uint16_t range = sizeToRead > sizeWritten ? sizeWritten : sizeToRead;
  for(uint32_t i = 0 ; i < range ; i++)
  {
    ptr[i] = endBuffer[i];
  }
}

int32_t readable2()
{
  return sizeWritten;
}

int32_t write2(void * buf, uint32_t sizeToWrite)
{
  sizeWritten = sizeToWrite;
  uint8_t * ptr = (uint8_t*)buf;
  for(uint32_t i = 0 ; i < sizeToWrite ; i++)
  {
    endBuffer[i] = ptr[i];
  }
}

int32_t writeable2()
{
  return 1;
}

/// end of mock

struct TM_state {
  uint8_t called;
  char rcvString[OUTGOING_BUFFER_SIZE];
};

void callback2(TM_state* s, TM_msg* m)
{
  s->called = 1;
  char str[OUTGOING_BUFFER_SIZE] = {0};
  if(emplace(m,str,OUTGOING_BUFFER_SIZE))
  {
    strcpy(s->rcvString,str);
  }
}

TEST publish_string()
{
  for(uint16_t i = 0 ; i < OUTGOING_BUFFER_SIZE ; i++)
  {
    endBuffer[i] = 0;
  }
  sizeWritten = 0;

  TM_state state;

  TM_transport transport;
  transport.read = read2;
  transport.write = write2;
  transport.readable = readable2;
  transport.writeable = writeable2;

  char topic[] = "topic";
  char message[] = "someMessage";

  init_telemetry(&state,&transport);

  subscribe("topic",callback2);

  publish(topic, message);

  update_telemetry(0);

  ASSERT_EQ(state.called, 1);

  ASSERT_STR_EQ(message,state.rcvString);

  PASS();
}

SUITE(pub_sub_string_suite) {
  RUN_TEST(publish_string);
}
