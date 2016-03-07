#include "test.h"

TEST update_int8()
{
  TM_msg dummy;
  char topic[128] = "int8";
  int8_t buf = -64;
  dummy.type = TM_int8;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;
  dummy.topic = topic;

  int8_t destination;

  if(!update_i8(&dummy, "int8",  &destination))
  {
    FAIL();
  }
  ASSERT_EQ_FMT(buf, destination,"%u");

  PASS();
}

TEST update_int16()
{
  TM_msg dummy;
  char topic[128] = "int16";
  int16_t buf = -64;
  dummy.type = TM_int16;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;
  dummy.topic = topic;

  int16_t destination;

  if(!update_i16(&dummy, "int16",  &destination))
  {
    FAIL();
  }
  ASSERT_EQ_FMT(buf, destination,"%u");

  PASS();
}


TEST update_int32()
{
  TM_msg dummy;
  char topic[128] = "int32";
  int32_t buf = -64;
  dummy.type = TM_int32;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;
  dummy.topic = topic;

  int32_t destination;

  if(!update_i32(&dummy, "int32",  &destination))
  {
    FAIL();
  }
  ASSERT_EQ_FMT(buf, destination,"%u");

  PASS();
}




SUITE(update_int_suite) {
  RUN_TEST(update_int8);
  RUN_TEST(update_int16);
  RUN_TEST(update_int32);
}
