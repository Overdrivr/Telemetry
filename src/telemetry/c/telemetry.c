#include "telemetry.h"

void initTelemetry(TM_state* s)
{

}

int emplace(TM_msg m, char * buf, size_t bufSize)
{

}

int emplace(TM_msg* m, uint8_t* dst)
{

}

int emplace(TM_msg* m, uint16_t* dst)
{

}

int emplace(TM_msg* m, uint32_t* dst)
{

}

int emplace(TM_msg* m, int8_t* dst)
{

}

int emplace(TM_msg* m, int16_t* dst)
{

}

int emplace(TM_msg* m, int32_t* dst)
{

}

int emplace(TM_msg* m, float* dst)
{

}

void publish(const char * topic, char *   msg)
{

}

void publish(const char * topic, uint8_t  msg)
{

}

void publish(const char * topic, uint16_t msg)
{

}

void publish(const char * topic, uint32_t msg)
{

}

void publish(const char * topic, int8_t   msg)
{

}

void publish(const char * topic, int16_t  msg)
{

}

void publish(const char * topic, int32_t  msg)
{

}

void publish(const char * topic, float    msg)
{

}

void subscribe(char * topic, void (*callback)(TM_state* s, TM_msg* m))
{

}

void update(float elapsedTime)
{

}
