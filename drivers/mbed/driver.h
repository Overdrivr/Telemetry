/*
    Driver (hardware-specific) routines for ARM Mbed platform
*/

#include "BufferedSerial.h"
static BufferedSerial pc(USBTX, USBRX);

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
    *(uint8_t*)(buf) = pc.getc();
    return 1;
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
    pc.write(buf,sizeToWrite);
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
    return pc.readable();
}

/*
  writeable
  This functions returns whether or not there is available space in
  the TX buffer

  @returns 0 if there is no space, 1 otherwise.

*/
int32_t writeable()
{
    return pc.writeable();
}
