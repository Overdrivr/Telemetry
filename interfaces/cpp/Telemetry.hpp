#include "c_api/telemetry.h"

class Telemetry
{
    public:
      Telemetry(TM_state* userData, uint32_t bauds = 9600);

      uint32_t cast(TM_msg * m, char * buf, size_t bufSize);
      uint32_t cast_u8(TM_msg * m, uint8_t * dst);
      uint32_t cast_u16(TM_msg * m, uint16_t * dst);
      uint32_t cast_u32(TM_msg * m, uint32_t * dst);
      uint32_t cast_i8(TM_msg * m, int8_t * dst);
      uint32_t cast_i16(TM_msg * m, int16_t * dst);
      uint32_t cast_i32(TM_msg * m, int32_t * dst);
      uint32_t cast_f32(TM_msg * m, float * dst);

      void pub(const char * topic, char * msg);
      void publish_u8(const char * topic, uint8_t msg);
      void publish_u16(const char * topic, uint16_t msg);
      void publish_u32(const char * topic, uint32_t msg);
      void publish_i8(const char * topic, int8_t msg);
      void publish_i16(const char * topic, int16_t msg);
      void publish_i32(const char * topic, int32_t msg);
      void publish_f32(const char * topic, float msg);

      void subscribe(void (*callback)(TM_state * s, TM_msg * m));

      void update();

    private:
      TM_transport transport;
};
