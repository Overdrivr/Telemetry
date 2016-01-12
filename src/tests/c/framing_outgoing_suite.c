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

  printf("%x\n",incomingBuffer[0]);
  printf("%x\n",incomingBuffer[1]);
  printf("%x\n",incomingBuffer[2]);

  ASSERT_EQ_FMT(3,amount,"%d");
  // TODO : Check mem
}

SUITE(framing_outgoing_suite) {
  RUN_TEST(framing_simple_frame);
}
