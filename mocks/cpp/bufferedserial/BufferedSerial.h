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

    void baud(uint32_t bauds);

    uint8_t getc();

    int32_t readable();

    int32_t write(void * data, uint32_t bufSize);
    int32_t writeable();

  private:
    std::queue<uint8_t> loopqueue;
};

#endif
