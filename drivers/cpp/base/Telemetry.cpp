#include "Telemetry.hpp"
#include "c_api/telemetry.h"

/*
  Driver specific routines. You must implement these 4 functions (read, write,
  readable, writeable) to support a new platform.
  See drivers/cpp/mbed/Telemetry.cpp for a practical example.
*/

/*
  read
  This functions reads from the driver (UART, serial port, http, etc.) and
  places into the supplied buffer `buf` at most `sizeToRead` bytes.

  @param buf The buffer in which to place the read bytes
  @param sizeToRead The maximum amount of bytes to read

  @returns the actual amount of characters read. Can be lower than sizeToRead if
    the driver has no more available data

*/
int32_t read(void * buf, uint32_t sizeToRead)
{
    // Exemple
    /*
    uint8_t * b = (uint8_t *)buff;
    for(uint32_t i = 0 ; i < sizeToRead ; i++)
    {
      if(!serial.available())
        return i;
      b[i] = pc.getc();
    }
    */
    return sizeToRead;
}

/*
  write
  This functions writes at most `sizeToWrite` bytes into the buffer `buf`

  @param buf The buffer in which to place the characters
  @param sizeToRead The maximum amount of bytes to write

  @returns 0 if everything went well.

*/
int32_t write(void * buf, uint32_t sizeToWrite)
{
    // Exemple
    /*
      serial.write(buf,sizeToWrite);
    */
    return 0;
}

/*
  readable
  This functions returns whether or not there are available bytes in
  the RX buffer

  @returns The amount of available characters.

*/
int32_t readable()
{
    uint32_t amount = 0;

    // Exemple
    /*
    amount = serial.readable();
    */

    return amount;
}

/*
  writeable
  This functions returns whether or not there is available space in
  the TX buffer

  @returns 0 if there is no space, 1 otherwise.

*/
int32_t writeable()
{
    uint32_t available = 0;

    // Exemple
    /*
    available = pc.writeable();
    */

    return available;
}


/*
  Main interface implementation - You should not need to modify it.
*/

Telemetry::Telemetry(uint32_t bauds)
{
    transport.read = read;
    transport.write = write;
    transport.readable = readable;
    transport.writeable = writeable;

    init_telemetry(&transport);

    //pc.baud(bauds);
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

void Telemetry::sub(void (*callback)(TM_state * s, TM_msg * m),
                    TM_state* userData)
{
    subscribe(callback,userData);
}

void Telemetry::update()
{
    update_telemetry(0);
}
