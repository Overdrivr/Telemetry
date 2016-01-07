#include "test.h"
#include "telemetry.h"

TEST_CASE( "Factorials are computed", "[factorial]" )
{
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

struct TM_state {
  bool called;
};

void callback(TM_state* s, TM_msg* m)
{
    s->called = true;
}

TEST_CASE( "Looped-back telemetry")
{
  TM_state p;
  initTelemetry(&p);

  SECTION("subscribed callback should be called on update")
  {
    p.called = false;

    subscribe("someChannel",callback);
    publish("someChannel", 0);
    update(0);

    REQUIRE(p.called == true);
  }

  SECTION("subscribed callback to a different channel should not be called on update")
  {
    p.called = false;

    subscribe("someChannel",callback);
    publish("someOtherChannel", 0);
    update(0);

    REQUIRE(p.called == false);
  }
}
