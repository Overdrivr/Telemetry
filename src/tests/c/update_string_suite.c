#include "test.h"

TEST update_string()
{
  TM_msg dummy;
  char buf[] = "Hello, World!";
  char topic[128] = "string";
  dummy.type = TM_string;
  dummy.buffer = (void *)buf;
  dummy.size = strlen(buf);
  dummy.topic = topic;

  char destination[32];

  if(!update(&dummy, topic, destination, 32))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(strlen(destination), strlen(buf),"%d");
  ASSERT_STR_EQ(destination, buf);

  PASS();
}

TEST update_string_exact_fit()
{
  TM_msg dummy;
  char buf[] = "Hello, World!";
  char topic[128] = "string_exact_fit";
  dummy.type = TM_string;
  dummy.buffer = (void *)buf;
  dummy.size = strlen(buf);
  dummy.topic = topic;

  char destination[14];

  if(!update(&dummy, topic, destination, 14))
  {
    FAIL();
  }

  ASSERT_EQ_FMT(strlen(destination), strlen(buf),"%d");
  ASSERT_STR_EQ(destination, buf);

  PASS();
}

TEST update_string_truncated()
{
  TM_msg dummy;
  char buf[] = "Hello, World!";
  char topic[128] = "string_truncated";
  dummy.type = TM_string;
  dummy.buffer = (void *)buf;
  dummy.size = strlen(buf);
  dummy.topic = topic;

  char destination[10];

  if(!update(&dummy,topic, destination, 10))
  {
    FAIL();
  }

  char expected[] = "Hello, Wo";

  ASSERT_EQ_FMT(strlen(destination), strlen(expected),"%d");
  ASSERT_STR_EQ(destination, expected);

  PASS();
}

SUITE(update_message_suite) {
  RUN_TEST(update_string);
  RUN_TEST(update_string_exact_fit);
  RUN_TEST(update_string_truncated);
}
