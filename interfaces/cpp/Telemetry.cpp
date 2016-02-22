#include driver.h
// C++ interface

Telemetry::Telemetry(TM_state* userData, uint32_t bauds)
{
    transport.read = read;
    transport.write = write;
    transport.readable = readable;
    transport.writeable = writeable;

    init_telemetry(userData, &transport);

    pc.baud(bauds);
}

uint32_t Telemetry::cast(TM_msg * m, char * buf, size_t bufSize)
{
    return emplace(m,buf,bufSize);
}

uint32_t Telemetry::cast_u8(TM_msg * m, uint8_t * dst)
{
    return emplace_u8(m,dst);
}

uint32_t Telemetry::cast_u16(TM_msg * m, uint16_t * dst)
{
    return emplace_u16(m,dst);
}

uint32_t Telemetry::cast_u32(TM_msg * m, uint32_t * dst)
{
    return emplace_u32(m,dst);
}

uint32_t Telemetry::cast_i8(TM_msg * m, int8_t * dst)
{
    return emplace_i8(m,dst);
}

uint32_t Telemetry::cast_i16(TM_msg * m, int16_t * dst)
{
    return emplace_i16(m,dst);
}

uint32_t Telemetry::cast_i32(TM_msg * m, int32_t * dst)
{
    return emplace_i32(m,dst);
}

uint32_t Telemetry::cast_f32(TM_msg * m, float * dst)
{
    return emplace_f32(m,dst);
}

void Telemetry::pub(const char * topic, char * msg)
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

void Telemetry::sub(void (*callback)(TM_state * s, TM_msg * m))
{
    subscribe(callback);
}

void Telemetry::update()
{
    update_telemetry(0);
}
