#include "telemetry.h"

struct parameters {
  float P;
}

void P(state* s, message* m){
  // Check message is of expected type
  if(m->type == type::float32){
    // Then put the received message (a value) into a variable
    float value;
    if(emplace(m, &value))
    {
      // If everything went well, store it the state
      // the new value will then be accessible in the main with parameters->P
      state->P = value;
    }
  }
}

int main()
{
  parameters p;
  int32_t d = 1.f;

  initTelemetry(&p);

  subscribe("Proportional",P);

  for( ; ; )
  {
    d = parameters->P;
    publish("Derivative", d);
    update(0);
  }

  return 0;
}
