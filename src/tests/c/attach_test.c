#include "test.h"
#include "dictionnary.h"

/// Mock of transport (serial). write is piped back to read
static uint8_t endBuffer[OUTGOING_BUFFER_SIZE];
static uint32_t sizeWritten;
static uint32_t sizeRead;

int32_t read(void * buf, uint32_t sizeToRead)
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

int32_t readable()
{
  return sizeWritten;
}

int32_t write(void * buf, uint32_t sizeToWrite)
{
  sizeWritten = sizeToWrite;
  uint8_t * ptr = (uint8_t*)buf;
  int32_t i;
  for(i = 0 ; i < sizeToWrite ; i++)
  {
    endBuffer[i] = ptr[i];
  }
}

int32_t writeable()
{
  return 1;
}

// Actual tests

TEST test_attach_all_types()
{
  TM_transport transport;
  transport.read = read;
  transport.write = write;
  transport.readable = readable;
  transport.writeable = writeable;

  init_telemetry(&transport);

  // Test attach float to topic foo
  float value = 1.23e4;

  attach_f32("foo",&value);
  publish_f32("foo", 0.f);
  if((value - 1.23e4) > 0.001)
  {
    FAIL();
  }
  update_telemetry(0);
  if((value - 0) > 0.001)
  {
    FAIL();
  }

  // reset buffers
  sizeWritten = 0;
  sizeRead = 0;

  // Test attach float to topic bar
  float value2 = 5.67e8;

  attach_f32("bar",&value2);
  publish_f32("bar", 1.23);
  if((value - 5.67e8) > 0.001)
  {
    FAIL();
  }
  update_telemetry(0);
  if((value - 1.23) > 0.001)
  {
    FAIL();
  }

  // reset buffers
  sizeWritten = 0;
  sizeRead = 0;

  // Test attach uint8 to topic foo
  uint8_t value_u8 = 255;

  attach_u8("foo",&value_u8);
  publish_u8("foo", 127);
  ASSERT_EQ_FMT(255, value_u8, "%d");
  update_telemetry(0);
  ASSERT_EQ_FMT(127, value_u8, "%d");

  PASS();
}

SUITE(attach_suite) {
  RUN_TEST(test_attach_all_types);
}
