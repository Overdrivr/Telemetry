#ifndef ARDUINO_HARDWARE_SERIAL_HPP_
#define ARDUINO_BUFFERED_SERIAL_HPP_

#include <queue>
#include "stdint.h"
#include "stddef.h"
/*
    A mock of the serial driver for Arduino.
    Original driver based on stream : https://github.com/arduino/Arduino/blob/master/hardware/arduino/avr/cores/arduino/Stream.h
    This mock is a loop driver. Anything written with write will later be readable with readBytes
*/

class HardwareSerial
{
  public:
    HardwareSerial();
    ~HardwareSerial();

    void begin(unsigned long bauds);

    int available();
    int availableForWrite();

    size_t readBytes(char * buffer, size_t length);
    size_t write(char * data, uint32_t bufSize);

  private:
    std::queue<char> loopqueue;
};

HardwareSerial Serial;

#endif
