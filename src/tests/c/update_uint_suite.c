#include "test.h"

TEST update_uint8()
{
  TM_msg dummy;
  char topic[128] = "uint8";
  uint8_t buf = 64;
  dummy.type = TM_uint8;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;
  dummy.topic = topic;

  uint8_t destination;

  if(!update_u8(&dummy, "uint8",  &destination))
  {
    FAIL();
  }
  ASSERT_EQ_FMT(buf, destination,"%u");

  PASS();
}

TEST update_uint16()
{
  TM_msg dummy;
  char topic[128] = "uint16";
  uint16_t buf = 64;
  dummy.type = TM_uint16;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;
  dummy.topic = topic;

  uint16_t destination;

  if(!update_u16(&dummy, "uint16",  &destination))
  {
    FAIL();
  }
  ASSERT_EQ_FMT(buf, destination,"%u");

  PASS();
}


TEST update_uint32()
{
  TM_msg dummy;
  char topic[128] = "uint32";
  uint32_t buf = 64;
  dummy.type = TM_uint32;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;
  dummy.topic = topic;

  uint32_t destination;

  if(!update_u32(&dummy, "uint32",  &destination))
  {
    FAIL();
  }
  ASSERT_EQ_FMT(buf, destination,"%u");

  PASS();
}




SUITE(update_uint_suite) {
  RUN_TEST(update_uint8);
  RUN_TEST(update_uint16);
  RUN_TEST(update_uint32);
}
