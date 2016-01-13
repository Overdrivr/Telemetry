#include "test.h"
#include "framing.h"

TEST framing_simple_frame()
{
  uint8_t incomingBuffer[12] = {0};

  initialize_framing();
  outgoing_storage(incomingBuffer,12);

  begin();
  append(0xFF);
  uint32_t amount = end();

  ASSERT_EQ_FMT(3,amount,"%d");

  uint8_t expected[] = {0xF7, 0xFF, 0x7F};
  uint16_t range = amount > 3 ? 3 : amount;
  for(uint16_t i = 0 ; i < range ; i++)
  {
    ASSERT_EQ_FMT(expected[i],incomingBuffer[i],"%x");
  }

  PASS();
}

TEST framing_with_escaping()
{
  uint8_t incomingBuffer[12] = {0};

  initialize_framing();
  outgoing_storage(incomingBuffer,12);

  begin();
  append(0xF7);
  append(0x7F);
  append(0x7D);
  uint32_t amount = end();

  ASSERT_EQ_FMT(8,amount,"%d");

  uint8_t expected[] = {0xF7, 0x7D, 0xF7, 0x7D, 0x7F, 0x7D, 0x7D, 0x7F};
  uint16_t range = amount > 8 ? 8 : amount;
  for(uint16_t i = 0 ; i < range ; i++)
  {
    ASSERT_EQ_FMT(expected[i],incomingBuffer[i],"%x");
  }

  PASS();
}

TEST framing_overflow()
{
  uint8_t incomingBuffer[3] = {0};

  initialize_framing();
  outgoing_storage(incomingBuffer,3);

  begin();
  append(0xFF);
  append(0xFF);
  uint32_t amount = end();

  ASSERT_EQ_FMT(0,amount,"%d");

  PASS();
}

SUITE(framing_outgoing_suite) {
  RUN_TEST(framing_simple_frame);
  RUN_TEST(framing_with_escaping);
  RUN_TEST(framing_overflow);
}
