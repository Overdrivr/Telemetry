#include "test.h"
#include "telemetry.h"

TEST emplace_float32()
{
  TM_msg dummy;
  float buf = 64;
  dummy.type = TM_float32;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  float destination;

  if(!emplace_f32(&dummy, &destination))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(buf, destination,"%f");

  PASS();
}

TEST emplace_float32_neg()
{
  TM_msg dummy;
  float buf = -64;
  dummy.type = TM_float32;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  float destination;

  if(!emplace_f32(&dummy, &destination))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(buf, destination,"%f");

  PASS();
}

TEST emplace_float32_decimals()
{
  TM_msg dummy;
  float buf = 64.123456;
  dummy.type = TM_float32;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  float destination;

  if(!emplace_f32(&dummy, &destination))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(buf, destination,"%f");

  PASS();
}

TEST emplace_float32_decimals_neg()
{
  TM_msg dummy;
  float buf = -64.123456;
  dummy.type = TM_float32;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  float destination;

  if(!emplace_f32(&dummy, &destination))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(buf, destination,"%f");

  PASS();
}

SUITE(emplace_float_suite) {
  RUN_TEST(emplace_float32);
  RUN_TEST(emplace_float32_neg);
  RUN_TEST(emplace_float32_decimals);
  RUN_TEST(emplace_float32_decimals_neg);
}
