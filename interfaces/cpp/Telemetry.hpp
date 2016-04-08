#ifndef TELEMETRY_HPP_
#define TELEMETRY_HPP_

#include "telemetry_config.h"

#ifdef TELEMETRY_ARDUINO_DISTRIBUTION
#include "telemetry_utils.h"
#else
#include "c_api/telemetry_utils.h"
#endif

class Telemetry
{
    public:
#ifdef TELEMETRY_ARDUINO_DISTRIBUTION
      Telemetry();
#else
      Telemetry(uint32_t bauds = 9600);
#endif

      void begin(uint32_t bauds = 9600);

      //void attach_to(const char * topic, );
      void attach_f32_to(const char * topic, float * variable);
      void attach_u8_to(const char * topic, uint8_t * variable);
      void attach_u16_to(const char * topic, uint16_t * variable);
      void attach_u32_to(const char * topic, uint32_t * variable);
      void attach_i8_to(const char * topic, int8_t * variable);
      void attach_i16_to(const char * topic, int16_t * variable);
      void attach_i32_to(const char * topic, int32_t * variable);

      TM_transport * get_transport();

      void pub(const char * topic, const char * msg);
      void pub_u8(const char * topic, uint8_t msg);
      void pub_u16(const char * topic, uint16_t msg);
      void pub_u32(const char * topic, uint32_t msg);
      void pub_i8(const char * topic, int8_t msg);
      void pub_i16(const char * topic, int16_t msg);
      void pub_i32(const char * topic, int32_t msg);
      void pub_f32(const char * topic, float msg);

      void sub(void (*callback)(TM_state * s, TM_msg * m), TM_state* userData);

      void update();

    private:
      TM_transport transport;
};

#endif
