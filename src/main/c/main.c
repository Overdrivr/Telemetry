#include "telemetry.h"

struct TM_state {
  float P;
};

void callback(TM_state* s, TM_msg* m){
  // Check message is of expected type
  if(m->type == TM_float32){
    // Then put the received message (a value) into a variable
    float value;
    if(emplace_f32(m, &value))
    {
      // If everything went well, store it the state
      // the new value will then be accessible in the main with parameters->P
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
