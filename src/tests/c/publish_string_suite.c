#include "test.h"
#include "telemetry.h"

struct TM_state {

};

int32_t read2(void * buf, uint32_t sizeToRead)
{

}

int32_t readable2()
{

}

static uint8_t endBuffer[OUTGOING_BUFFER_SIZE];
static uint32_t sizeWritten;

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

  publish(topic, message);

  PASS();
}

SUITE(publish_string_suite) {
  RUN_TEST(publish_string);
}
