#include "test.h"
#include "framing.h"

static uint8_t rcv_data[12];
static uint32_t rcv_size;
static uint8_t complete;

void callback_incoming(uint8_t * storage, uint32_t occupiedSize)
{
  complete = 1;
  uint32_t amount = occupiedSize > 12 ? 12 : occupiedSize;
  rcv_size = amount;
  memcpy(rcv_data, storage, amount);
}

TEST framing_simple_feed()
{
  uint8_t incomingBuffer[12] = {0};
  complete = 0;
  rcv_size = 0;
  uint32_t i;
  for(i = 0 ; i < 12 ; i++)
    rcv_data[i] = 0;

  initialize_framing();
  incoming_storage(incomingBuffer,12);
  set_on_incoming_frame(callback_incoming);

  uint8_t feed_data[] = {0xF7,0xFF,0x7F};

  for(i = 0 ; i < 3 ; i++)
  {
    feed(feed_data[i]);
  }

  ASSERTm("Valid frame was not detected. callback not triggered.", complete);
  ASSERT_EQ_FMT(feed_data[1],rcv_data[0],"%d");
  ASSERT_EQ_FMT(1,rcv_size,"%d");

  PASS();
}

TEST framing_corrupted_then_valid_feed()
{
  uint8_t incomingBuffer[12] = {0};
  complete = 0;
  rcv_size = 0;
  uint32_t i;
  for(i = 0 ; i < 12 ; i++)
    rcv_data[i] = 0;

  initialize_framing();
  incoming_storage(incomingBuffer,12);
  set_on_incoming_frame(callback_incoming);

  uint8_t feed_data[] = {0xF7,0xFF,0xF7,0xDD,0x7F};

  for(i = 0 ; i < 5 ; i++)
  {
    feed(feed_data[i]);
  }

  ASSERTm("Valid frame was not detected. callback not triggered.", complete);
  ASSERT_EQ_FMT(1,rcv_size,"%d");
  ASSERT_EQ_FMT(feed_data[3],rcv_data[0],"%d");

  PASS();
}

TEST framing_basic_escaping_feed()
{
  uint8_t incomingBuffer[12] = {0};
  complete = 0;
  rcv_size = 0;
  uint32_t i;

  for(i = 0 ; i < 12 ; i++)
    rcv_data[i] = 0;

  initialize_framing();
  incoming_storage(incomingBuffer,12);
  set_on_incoming_frame(callback_incoming);

  uint8_t feed_data[] = {0xF7,0x7D,0xFF,0xDD,0x7F}; // useless ESC for test only

  for(i = 0 ; i < 5 ; i++)
  {
    feed(feed_data[i]);
  }

  ASSERTm("Valid frame was not detected. callback not triggered.", complete);
  ASSERT_EQ_FMT(2,rcv_size,"%d");
  ASSERT_EQ_FMT(feed_data[2],rcv_data[0],"%d");
  ASSERT_EQ_FMT(feed_data[3],rcv_data[1],"%d");

  PASS();
}

TEST framing_all_escaped_flags_feed()
{
  uint8_t incomingBuffer[12] = {0};
  complete = 0;
  rcv_size = 0;
  uint32_t i;

  for(i = 0 ; i < 12 ; i++)
    rcv_data[i] = 0;

  initialize_framing();
  incoming_storage(incomingBuffer,12);
  set_on_incoming_frame(callback_incoming);

  uint8_t feed_data[] = {0xF7,0x7D,0x7F,0x7D,0xF7,0x7D,0x7D,0x7F};

  for(i = 0 ; i < 8 ; i++)
  {
    feed(feed_data[i]);
  }

  ASSERTm("Valid frame was not detected. callback not triggered.", complete);
  ASSERT_EQ_FMT(3,rcv_size,"%d");
  ASSERT_EQ_FMT(feed_data[2],rcv_data[0],"%d");
  ASSERT_EQ_FMT(feed_data[4],rcv_data[1],"%d");
  ASSERT_EQ_FMT(feed_data[6],rcv_data[2],"%d");

  PASS();
}

TEST framing_overflowing_feed()
{
  uint8_t incomingBuffer[3] = {0};
  complete = 0;
  rcv_size = 0;
  uint32_t i;

  for(i = 0 ; i < 12 ; i++)
    rcv_data[i] = 0;

  initialize_framing();
  incoming_storage(incomingBuffer,3);
  set_on_incoming_frame(callback_incoming);

  uint8_t feed_data[] = {0xF7,0x7D,0x7F,0x7D,0xF7,0x7D,0x7D,0x7F};

  for(i = 0 ; i < 8 ; i++)
  {
    feed(feed_data[i]);
  }

  ASSERT_FALSEm("Valid frame was detected while not expected to.", complete);
  ASSERT_EQ_FMT(0,rcv_size,"%d");

  PASS();
}

SUITE(framing_incoming_suite) {
  RUN_TEST(framing_simple_feed);
  RUN_TEST(framing_corrupted_then_valid_feed);
  RUN_TEST(framing_basic_escaping_feed);
  RUN_TEST(framing_all_escaped_flags_feed);
  RUN_TEST(framing_overflowing_feed);
}
