#include "test.h"
#include "telemetry.h"

extern SUITE(standard_flow_suite);

/* Add definitions that need to be in the test runner's main file. */
GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* command-line arguments, initialization. */

    /* Individual tests can be run directly. */
    /* RUN_TEST(x_should_equal_1); */

    /* Tests can also be gathered into test suites. */
    RUN_SUITE(standard_flow_suite);

    GREATEST_MAIN_END();        /* display results */
}
