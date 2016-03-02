#include "test.h"

TEST emplace_string()
{
  TM_msg dummy;
  char buf[] = "Hello, World!";
  dummy.type = TM_string;
  dummy.buffer = (void *)buf;
  dummy.size = strlen(buf);

  char destination[32];

  if(!emplace(&dummy, destination, 32))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(strlen(destination), strlen(buf),"%d");
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

  if(!emplace(&dummy, destination, 14))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(strlen(destination), strlen(buf),"%d");
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

  if(!emplace(&dummy, destination, 10))
  {
    FAIL();
  }

  char expected[] = "Hello, Wo";

  ASSERT_EQ_FMT(strlen(destination), strlen(expected),"%d");
  ASSERT_STR_EQ(destination, expected);

  PASS();
}

SUITE(emplace_message_suite) {
  RUN_TEST(emplace_string);
  RUN_TEST(emplace_string_exact_fit);
  RUN_TEST(emplace_string_truncated);
}
