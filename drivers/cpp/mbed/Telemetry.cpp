#include "Telemetry.hpp"
#include "c_api/telemetry_core.h"
#include "BufferedSerial.h"

static BufferedSerial pc(USBTX, USBRX);

int32_t read(void * buf, uint32_t sizeToRead)
{
    *(uint8_t*)(buf) = pc.getc();
    return 1;
}

int32_t write(void * buf, uint32_t sizeToWrite)
{
    pc.write(buf,sizeToWrite);
    return 0;
}

int32_t readable()
{
    return pc.readable();
}

int32_t writeable()
{
    return pc.writeable();
}

Telemetry::Telemetry(uint32_t bauds)
{
    transport.read = read;
    transport.write = write;
    transport.readable = readable;
    transport.writeable = writeable;

    init_telemetry(&transport);

    pc.baud(bauds);
}

void Telemetry::begin(uint32_t bauds)
{
    pc.baud(bauds);
}

TM_transport * Telemetry::get_transport()
{
  return &transport;
}

void Telemetry::pub(const char * topic, const char * msg)
{
    publish(topic,msg);
}

void Telemetry::pub_u8(const char * topic, uint8_t msg)
{
    publish_u8(topic,msg);
}

void Telemetry::pub_u16(const char * topic, uint16_t msg)
{
    publish_u16(topic,msg);
}

void Telemetry::pub_u32(const char * topic, uint32_t msg)
{
    publish_u32(topic,msg);
}

void Telemetry::pub_i8(const char * topic, int8_t msg)
{
    publish_i8(topic,msg);
}

void Telemetry::pub_i16(const char * topic, int16_t msg)
{
    publish_i16(topic,msg);
}

void Telemetry::pub_i32(const char * topic, int32_t msg)
{
    publish_i32(topic,msg);
}

void Telemetry::pub_f32(const char * topic, float msg)
{
    publish_f32(topic,msg);
}

void Telemetry::sub(void (*callback)(TM_state * s, TM_msg * m),
                    TM_state* userData)
{
    set_state(userData);
    subscribe(callback);
}

void Telemetry::update()
{
    update_telemetry(0);
}
