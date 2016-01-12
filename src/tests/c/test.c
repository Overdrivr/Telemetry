#include "test.h"
#include "telemetry.h"

extern SUITE(standard_flow_suite);
extern SUITE(emplace_message_suite);
extern SUITE(emplace_uint_suite);
extern SUITE(emplace_int_suite);

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(standard_flow_suite);
    RUN_SUITE(emplace_message_suite);
    RUN_SUITE(emplace_uint_suite);
    RUN_SUITE(emplace_int_suite);

    GREATEST_MAIN_END();
}
