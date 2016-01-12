#include "test.h"
#include "telemetry.h"

TEST emplace_int8()
{
  TM_msg dummy;
  int8_t buf = 64;
  dummy.type = TM_int8;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  int8_t destination;

  emplace_i8(&dummy, &destination);

  ASSERT_EQ_FMT(buf, destination,"%u");

  PASS();
}

TEST emplace_int8_neg()
{
  TM_msg dummy;
  int8_t buf = -64;
  dummy.type = TM_int8;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  int8_t destination;

  emplace_i8(&dummy, &destination);

  ASSERT_EQ_FMT(buf, destination,"%u");

  PASS();
}

TEST emplace_int16()
{
  TM_msg dummy;
  int16_t buf = 64;
  dummy.type = TM_int16;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  int16_t destination;

  emplace_i16(&dummy, &destination);

  ASSERT_EQ_FMT(buf, destination,"%d");

  PASS();
}

TEST emplace_int16_neg()
{
  TM_msg dummy;
  int16_t buf = -64;
  dummy.type = TM_int16;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  int16_t destination;

  emplace_i16(&dummy, &destination);

  ASSERT_EQ_FMT(buf, destination,"%d");

  PASS();
}

TEST emplace_int32()
{
  TM_msg dummy;
  int32_t buf = 64;
  dummy.type = TM_int32;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  int32_t destination;

  emplace_i32(&dummy, &destination);

  ASSERT_EQ_FMT(buf, destination,"%d");

  PASS();
}

TEST emplace_int32_neg()
{
  TM_msg dummy;
  int32_t buf = -64;
  dummy.type = TM_int32;
  dummy.buffer = (void *)&buf;
  dummy.size = 1;

  int32_t destination;

  emplace_i32(&dummy, &destination);

  ASSERT_EQ_FMT(buf, destination,"%d");

  PASS();
}

SUITE(emplace_int_suite) {
  RUN_TEST(emplace_int8);
  RUN_TEST(emplace_int16);
  RUN_TEST(emplace_int32);
  RUN_TEST(emplace_int8_neg);
  RUN_TEST(emplace_int16_neg);
  RUN_TEST(emplace_int32_neg);
}
