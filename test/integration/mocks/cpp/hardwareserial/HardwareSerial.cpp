#include "HardwareSerial.h"
#include <stdexcept>

HardwareSerial::HardwareSerial()
{ }

HardwareSerial::~HardwareSerial()
{ }

void HardwareSerial::begin(unsigned long bauds)
{ }

size_t HardwareSerial::readBytes(char * buffer, size_t length)
{
  if(this->loopqueue.empty())
    throw std::runtime_error("Trying to get uint8_t char from empty queue");

  size_t i = 0;
  while(i < length && !this->loopqueue.empty())
  {
      char c = this->loopqueue.front();
      this->loopqueue.pop();
      buffer[i] = c;
      i++;
  }

  return i;
}

int32_t HardwareSerial::available()
{
  return this->loopqueue.size();
}

size_t HardwareSerial::write(char * data, uint32_t bufSize)
{
  char * caster = static_cast<char*>(data);

  for(size_t i = 0 ; i < bufSize ; i++)
    this->loopqueue.push(caster[i]);
}

int32_t HardwareSerial::availableForWrite()
{
  return 1;
}
