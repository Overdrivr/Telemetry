#include "test.h"
#include "telemetry.h"

struct TM_state {
  uint8_t called;
};

void callback(TM_state* s, TM_msg* m)
{
  s->called = 1;
}

TEST subscribed_topic_should_trigger_callback()
{
  TM_state state;

  initTelemetry(&state);

  // TODO : Mock of shunt-transport

  state.called = 0;

  subscribe("topic",callback);

  publish("topic", "someMessage");

  updateTelemetry(0);

  ASSERT_EQ(state.called, 1);

  PASS();
}

TEST non_subscribed_topic_should_not_trigger_callback()
{
  TM_state state;

  initTelemetry(&state);

  // TODO : Mock of shunt-transport

  state.called = 0;

  subscribe("topic",callback);

  publish("otherTopic", "someMessage");

  updateTelemetry(0);

  ASSERT_EQ(state.called, 0);

  PASS();
}

/* Suites can group multiple tests with common setup. */
SUITE(standard_flow_suite) {
    RUN_TEST(subscribed_topic_should_trigger_callback);
    RUN_TEST(non_subscribed_topic_should_not_trigger_callback);
}
