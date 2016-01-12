#include "test.h"
#include "telemetry.h"

TEST emplace_string()
{
  TM_msg dummy;
  char buf[] = "Hello, World!";
  dummy.type = TM_string;
  dummy.buffer = (void *)buf;
  dummy.size = strlen(buf);

  char destination[32];

  uint32_t size = emplace(&dummy, destination, 32);

  ASSERT_EQ_FMT(size, strlen(buf),"%d");
  ASSERT_STR_EQ(destination, buf);

  PASS();
}

TEST emplace_string_exact_fit()
{
  TM_msg dummy;
  char buf[] = "Hello, World!";
  dummy.type = TM_string;
  dummy.buffer = (void *)buf;
  dummy.size = strlen(buf);

  char destination[14];

  uint32_t size = emplace(&dummy, destination, 14);

  ASSERT_EQ_FMT(size, strlen(buf),"%d");
  ASSERT_STR_EQ(destination, buf);

  PASS();
}

TEST emplace_string_truncated()
{
  TM_msg dummy;
  char buf[] = "Hello, World!";
  dummy.type = TM_string;
  dummy.buffer = (void *)buf;
  dummy.size = strlen(buf);

  char destination[10];

  uint32_t size = emplace(&dummy, destination, 10);

  char expected[] = "Hello, Wo";

  ASSERT_EQ_FMT(size, strlen(expected),"%d");
  ASSERT_STR_EQ(destination, expected);

  PASS();
}

//emplace_string_truncated

/* Suites can group multiple tests with common setup. */
SUITE(emplace_message_suite) {
    RUN_TEST(emplace_string);
    RUN_TEST(emplace_string_exact_fit);
    RUN_TEST(emplace_string_truncated);
}
