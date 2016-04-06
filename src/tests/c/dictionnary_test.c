#include "test.h"
#include "dictionnary.h"

TEST dictionnary_insert()
{
  struct nlist * hashtab[HASHSIZE];
  init_table(hashtab);

  float testvar = 0.f;

  install(hashtab, "foo", (void*)(&testvar), ptr_float32);

  // Test installed structure can be retrieved
  struct nlist * np = lookup(hashtab, "foo");
  if(np == NULL)
  {
    FAIL();
  }

  ASSERT_EQ(np->ptr_f32, &testvar);

  ASSERT_EQ(np->ptr_u8, NULL);
  ASSERT_EQ(np->ptr_u16, NULL);
  ASSERT_EQ(np->ptr_u32, NULL);
  ASSERT_EQ(np->ptr_i8, NULL);
  ASSERT_EQ(np->ptr_i16, NULL);
  ASSERT_EQ(np->ptr_i32, NULL);
  ASSERT_EQ(np->ptr_callback, NULL);

  ASSERT_EQ(*(np->ptr_f32),testvar);

  if(lookup(hashtab, "bar") != NULL)
  {
    FAIL();
  }

  PASS();
}


SUITE(dictionnary_suite) {
  RUN_TEST(dictionnary_insert);
}
