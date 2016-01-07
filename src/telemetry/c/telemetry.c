#include "telemetry.h"

void initTelemetry(state* s)
{

}

int emplace(message m, char * buf, size_t bufSize)
{

}

int emplace(message m, uint8_t *  dst)
{

}

int emplace(message m, uint16_t * dst)
{

}

int emplace(message m, uint32_t * dst)
{

}

int emplace(message m, int8_t *   dst)
{

}

int emplace(message m, int16_t *  dst)
{

}

int emplace(message m, int32_t *  dst)
{

}

void publish(char * topic, char *   msg)
{

}

void publish(char * topic, uint8_t  msg)
{

}

void publish(char * topic, uint16_t msg)
{

}

void publish(char * topic, uint32_t msg)
{

}

void publish(char * topic, int8_t   msg)
{

}

void publish(char * topic, int16_t  msg)
{

}

void publish(char * topic, int32_t  msg)
{

}

void publish(char * topic, float    msg)
{

}

void subscribe(char * topic, void (*callback)(state* s, message* m))
{

}

void update(float elapsedTime)
{
  
}
