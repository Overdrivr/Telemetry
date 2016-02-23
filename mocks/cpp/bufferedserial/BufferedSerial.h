#ifndef BUFFERED_SERIAL_HPP_
#define BUFFERED_SERIAL_HPP_

#include <queue>
#include "stdint.h"

enum pin
{
  USBTX,
  USBRX
};

/*
    A mock of the serial driver for Mbed.
    Original driver : https://developer.mbed.org/users/sam_grove/code/BufferedSerial/
*/

class BufferedSerial
{
  public:
    BufferedSerial(pin fakeTX, pin fakeRX);
    ~BufferedSerial();

    baud(uint32_t bauds);

    getc();

    readable();

    write(void * data, uint32_t bufSize);
    writeable();

  private:
    std::queue<char> loopqueue;
};

#endif
