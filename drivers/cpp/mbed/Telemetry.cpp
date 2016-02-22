#include "Telemetry.hpp"

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

void Telemetry::publish(const char * topic, char * msg)
{
    publish(topic,msg);
}

void Telemetry::publish_u8(const char * topic, uint8_t msg)
{
    publish_u8(topic,msg);
}

void Telemetry::publish_u16(const char * topic, uint16_t msg)
{
    publish_u16(topic,msg);
}

void Telemetry::publish_u32(const char * topic, uint32_t msg)
{
    publish_u32(topic,msg);
}

void Telemetry::publish_i8(const char * topic, int8_t msg)
{
    publish_i8(topic,msg);
}

void Telemetry::publish_i16(const char * topic, int16_t msg)
{
    publish_i16(topic,msg);
}

void Telemetry::publish_i32(const char * topic, int32_t msg)
{
    publish_i32(topic,msg);
}

void Telemetry::publish_f32(const char * topic, float msg)
{
    publish_f32(topic,msg);
}

void Telemetry::subscribe(void (*callback)(TM_state * s, TM_msg * m))
{
    subscribe(callback);
}

void Telemetry::setState(TM_state* userData)
{
    set_state(userData);
}

void Telemetry::update()
{
    update_telemetry(0);
}

uint32_t cast(TM_msg * m, char * buf, size_t bufSize)
{
    return emplace(m,buf,bufSize);
}

uint32_t cast_u8(TM_msg * m, uint8_t * dst)
{
    return emplace_u8(m,dst);
}

uint32_t cast_u16(TM_msg * m, uint16_t * dst)
{
    return emplace_u16(m,dst);
}

uint32_t cast_u32(TM_msg * m, uint32_t * dst)
{
    return emplace_u32(m,dst);
}

uint32_t cast_i8(TM_msg * m, int8_t * dst)
{
    return emplace_i8(m,dst);
}

uint32_t cast_i16(TM_msg * m, int16_t * dst)
{
    return emplace_i16(m,dst);
}

uint32_t cast_i32(TM_msg * m, int32_t * dst)
{
    return emplace_i32(m,dst);
}

uint32_t cast_f32(TM_msg * m, float * dst)
{
    return emplace_f32(m,dst);
}
