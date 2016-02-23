#include "c_api/telemetry_utils.h"

class Telemetry
{
    public:
      Telemetry(uint32_t bauds = 9600);
      // Need different names from C API otherwise calling a method will call
      // this method again and again
      void pub(const char * topic, char * msg);
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
