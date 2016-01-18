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

int32_t read(void * buf, uint32_t sizeToRead)
{

}

int32_t readable()
{

}

int32_t write(void * buf, uint32_t sizeToWrite)
{

}

int32_t writeable()
{

}

int main()
{
  TM_state state;
  TM_transport transport;
  transport.read = read;
  transport.write = write;
  transport.readable = readable;
  transport.writeable = writeable;

  init_telemetry(&state, &transport);

  int32_t d = 1.f;

  subscribe(callback);

  for( ; ; )
  {
    d = state.P;
    publish_i32("Derivative", d);
    update_telemetry(0);
  }

  return 0;
}
