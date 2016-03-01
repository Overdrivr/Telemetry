#include "BufferedSerial.h"
#include <stdexcept>

BufferedSerial::BufferedSerial(pin fakeTX, pin fakeRX)
{
}

BufferedSerial::~BufferedSerial()
{
}

void BufferedSerial::baud(uint32_t bauds)
{
}

uint8_t BufferedSerial::getc()
{
  if(this->loopqueue.empty())
    throw std::runtime_error("Trying to get uint8_tacter from empty queue");
  uint8_t c = this->loopqueue.front();
  this->loopqueue.pop();
  return c;
}

int32_t BufferedSerial::readable()
{
  return this->loopqueue.size();
}

int32_t BufferedSerial::write(void * data, uint32_t bufSize)
{
  uint8_t * caster = static_cast<uint8_t*>(data);

  for(uint32_t i = 0 ; i < bufSize ; i++)
    this->loopqueue.push(caster[i]);
}

int32_t BufferedSerial::writeable()
{
  return 1;
}
