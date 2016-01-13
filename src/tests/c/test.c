#include "test.h"
#include "telemetry.h"

extern SUITE(standard_flow_suite);
extern SUITE(emplace_message_suite);
extern SUITE(emplace_uint_suite);
extern SUITE(emplace_int_suite);
extern SUITE(emplace_float_suite);
extern SUITE(pub_sub_string_suite);
extern SUITE(framing_outgoing_suite);

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();

    RUN_SUITE(standard_flow_suite);
    RUN_SUITE(emplace_message_suite);
    RUN_SUITE(emplace_uint_suite);
    RUN_SUITE(emplace_int_suite);
    RUN_SUITE(emplace_float_suite);
    RUN_SUITE(pub_sub_string_suite);
    RUN_SUITE(framing_outgoing_suite);

    GREATEST_MAIN_END();
}
