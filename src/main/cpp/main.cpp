#include "telemetry.h"

struct TM_state {
  float P;
};

void callback(TM_state* s, TM_msg* m)
{
  if(m->type == TM_uint8)
  {
    uint8_t value;
    if(emplace_u8(m, &value))
    {
      s->P = value;
    }
  }
}

int main()
{
  TM_state p;
  int32_t d = 1.f;

  initTelemetry(&p);

  subscribe("Proportional",callback);

  for( ; ; )
  {
    d = p.P;
    publish_i32("Derivative", d);
    update(0);
  }

  return 0;
}
