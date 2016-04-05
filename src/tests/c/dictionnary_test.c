#include "test.h"
#include "dictionnary.h"

TEST dictionnary_insert()
{

  struct nlist * hashtab[HASHSIZE];
  init_table(hashtab);
  install(hashtab, "foo", "bar");

  if(lookup(hashtab, "foo") == NULL)
  {
    FAIL();
  }

  if(lookup(hashtab, "bar") != NULL)
  {
    FAIL();
  }

  PASS();
}


SUITE(dictionnary_suite) {
  RUN_TEST(dictionnary_insert);
}
