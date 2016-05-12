#include "test.h"

TEST match_simple()
{
  TM_msg dummy;
  char topic[] = "foo";
  dummy.topic = topic;

  ASSERT_EQ_FMT(match(&dummy, topic),1,"%u");
  ASSERT_EQ_FMT(match(&dummy, "foo"),1,"%u");
  ASSERT_EQ_FMT(match(&dummy, "bar"),0,"%u");
  PASS();
}

TEST match_with_spaces()
{
  TM_msg dummy;
  char topic[] = "foo with spaces";
  dummy.topic = topic;

  ASSERT_EQ_FMT(match(&dummy, topic),1,"%u");
  ASSERT_EQ_FMT(match(&dummy, "foo with spaces"),1,"%u");
  ASSERT_EQ_FMT(match(&dummy, "foo"),0,"%u");
  ASSERT_EQ_FMT(match(&dummy, "bar"),0,"%u");
  PASS();
}

TEST match_with_special_chars()
{
  TM_msg dummy;
  char topic[] = "/:@#";
  dummy.topic = topic;

  ASSERT_EQ_FMT(match(&dummy, topic),1,"%u");
  ASSERT_EQ_FMT(match(&dummy, "/:@#"),1,"%u");
  ASSERT_EQ_FMT(match(&dummy, "$#@:/"),0,"%u");
  ASSERT_EQ_FMT(match(&dummy, "bar"),0,"%u");
  PASS();
}

TEST fullmatch_test()
{
  TM_msg dummy;
  char topic[] = "foo";
  dummy.topic = topic;
  dummy.type = TM_uint8;

  ASSERT_EQ_FMT(fullmatch(&dummy, topic, TM_uint8),1,"%u");
  ASSERT_EQ_FMT(fullmatch(&dummy, topic, TM_int8),0,"%u");
  ASSERT_EQ_FMT(fullmatch(&dummy, "foo", TM_uint8),1,"%u");
  ASSERT_EQ_FMT(fullmatch(&dummy, "foo", TM_int8),0,"%u");
  ASSERT_EQ_FMT(fullmatch(&dummy, "bar", TM_uint8),0,"%u");
  ASSERT_EQ_FMT(fullmatch(&dummy, "bar", TM_int16),0,"%u");
  PASS();
}

SUITE(match_suite) {
  RUN_TEST(match_simple);
  RUN_TEST(match_with_spaces);
  RUN_TEST(match_with_special_chars);
  RUN_TEST(fullmatch_test);
}
