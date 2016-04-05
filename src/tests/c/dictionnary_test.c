#include "test.h"
#include "dictionnary.h"

TEST dictionnary_insert()
{
  install("foo","bar");

  if(lookup("foo") == NULL)
  {
    FAIL();
  }

  if(lookup("bar") != NULL)
  {
    FAIL();
  }

  PASS();
}


SUITE(dictionnary_suite) {
  RUN_TEST(dictionnary_insert);
}
