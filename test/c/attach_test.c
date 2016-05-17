#include "test.h"
#include "dictionnary.h"

/// Mock of transport (serial). write is piped back to read
static uint8_t endBuffer[OUTGOING_BUFFER_SIZE];
static uint32_t sizeWritten;
static uint32_t sizeRead;

int32_t read(uint8_t * buf, uint32_t sizeToRead)
{
  int32_t rem = sizeWritten - sizeRead;
  uint16_t range = sizeToRead > rem ? rem : sizeToRead;
  int32_t i;
  for(i = 0 ; i < range ; i++)
  {
    buf[i] = endBuffer[sizeRead + i];
    sizeRead++;
  }

}

int32_t readable()
{
  return sizeWritten;
}

int32_t write(uint8_t * buf, uint32_t sizeToWrite)
{
  sizeWritten = sizeToWrite;
  int32_t i;
  for(i = 0 ; i < sizeToWrite ; i++)
  {
    endBuffer[i] = buf[i];
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
  update_telemetry();
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
  update_telemetry();
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
  update_telemetry();
  ASSERT_EQ_FMT(127, value_u8, "%d");

  // reset buffers
  sizeWritten = 0;
  sizeRead = 0;

  uint16_t value_u16 = 65535;

  attach_u16("qux",&value_u16);
  publish_u16("qux", 127);
  ASSERT_EQ_FMT(65535, value_u16, "%d");
  update_telemetry();
  ASSERT_EQ_FMT(127, value_u16, "%d");

  // reset buffers
  sizeWritten = 0;
  sizeRead = 0;

  uint32_t value_u32 = 4294967295;

  attach_u32("qux",&value_u32);
  publish_u32("qux", 0);
  ASSERT_EQ_FMT(4294967295, value_u32, "%d");
  update_telemetry();
  ASSERT_EQ_FMT(0, value_u32, "%d");

  // reset buffers
  sizeWritten = 0;
  sizeRead = 0;

  int8_t value_i8 = -127;

  attach_i8("foo",&value_i8);
  publish_i8("foo", 127);
  ASSERT_EQ_FMT(-127, value_i8, "%d");
  update_telemetry();
  ASSERT_EQ_FMT(127, value_i8, "%d");

  // reset buffers
  sizeWritten = 0;
  sizeRead = 0;

  // Test attach uint8 to topic foo
  int16_t value_i16 = 32767;

  attach_i16("qux",&value_i16);
  publish_i16("qux", -32767);
  ASSERT_EQ_FMT(32767, value_i16, "%d");
  update_telemetry();
  ASSERT_EQ_FMT(-32767, value_i16, "%d");

  // reset buffers
  sizeWritten = 0;
  sizeRead = 0;

  // Test attach uint8 to topic foo
  int32_t value_i32 = 2147483647;

  attach_i32("qux",&value_i32);
  publish_i32("qux", -2147483647);
  ASSERT_EQ_FMT(2147483647, value_i32, "%d");
  update_telemetry();
  ASSERT_EQ_FMT(-2147483647, value_i32, "%d");

  PASS();
}

SUITE(attach_suite) {
  RUN_TEST(test_attach_all_types);
}
