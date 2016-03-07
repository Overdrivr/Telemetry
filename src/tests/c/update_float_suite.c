#include "test.h"

TEST update_float32()
{
  TM_msg dummy;
  char topic[128] = "float32";
  float buf = -64;
  dummy.type = TM_int8;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;
  dummy.topic = topic;

  float destination;

  if(!update_float32(&dummy, "float32",  &destination))
  {
    FAIL();
  }
  ASSERT_EQ_FMT(buf, destination,"%u");

  PASS();
}

TEST update_float32_neg()
{
  TM_msg dummy;
  char topic[128] = "float32_neg";
  float buf = -64;
  dummy.type = TM_int16;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;
  dummy.topic = topic;

  float destination;

  if(!update_float32(&dummy, "float32_neg",  &destination))
  {
    FAIL();
  }
  ASSERT_EQ_FMT(buf, destination,"%u");

  PASS();
}


TEST update_float32_decimals()
{
  TM_msg dummy;
  char topic[128] = "float32_decimals";
  float buf = -64.1235;
  dummy.type = TM_int32;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;
  dummy.topic = topic;

  float destination;

  if(!update_float32(&dummy, "float32_decimals",  &destination))
  {
    FAIL();
  }
  ASSERT_EQ_FMT(buf, destination,"%u");

  PASS();
}




SUITE(update_float_suite) {
  RUN_TEST(update_float32);
  RUN_TEST(update_float32_neg);
  RUN_TEST(update_float32_decimals);
}
