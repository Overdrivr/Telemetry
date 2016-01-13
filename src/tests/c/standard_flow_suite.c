#include "test.h"
#include "telemetry.h"

struct TM_state {
  uint8_t called;
};

void callback(TM_state* s, TM_msg* m)
{
  s->called = 1;
}


int32_t read(void * buf, uint32_t sizeToRead)
{

}

int32_t readable()
{

}

int32_t write(void * buf, uint32_t sizeToWrite)
{

}

int32_t writeable()
{

}

TEST non_subscribed_topic_should_not_trigger_callback()
{
  TM_state state;

  TM_transport transport;
  transport.read = read;
  transport.write = write;
  transport.readable = readable;
  transport.writeable = writeable;

  init_telemetry(&state,&transport);

  // TODO : Mock of shunt-transport

  state.called = 0;

  subscribe("topic",callback);

  publish("otherTopic", "someMessage");

  update_telemetry(0);

  ASSERT_EQ(state.called, 0);

  PASS();
}

/* Suites can group multiple tests with common setup. */
SUITE(standard_flow_suite) {
    RUN_TEST(non_subscribed_topic_should_not_trigger_callback);
}
