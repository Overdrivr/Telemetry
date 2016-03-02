#include "test.h"

TEST emplace_uint8()
{
  TM_msg dummy;
  uint8_t buf = 64;
  dummy.type = TM_uint8;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  uint8_t destination;

  if(!emplace_u8(&dummy, &destination))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(buf, destination,"%u");

  PASS();
}

TEST emplace_uint16()
{
  TM_msg dummy;
  uint16_t buf = 64;
  dummy.type = TM_uint16;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  uint16_t destination;

  if(!emplace_u16(&dummy, &destination))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(buf, destination,"%d");

  PASS();
}

TEST emplace_uint32()
{
  TM_msg dummy;
  uint32_t buf = 64;
  dummy.type = TM_uint32;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  uint32_t destination;

  if(!emplace_u32(&dummy, &destination))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(buf, destination,"%d");

  PASS();
}

SUITE(emplace_uint_suite) {
  RUN_TEST(emplace_uint8);
  RUN_TEST(emplace_uint16);
  RUN_TEST(emplace_uint32);
}
