#include "BufferedSerial.h"
#include <stdexcept>

BufferedSerial::BufferedSerial(pin fakeTX, pin fakeRX)
{
}

BufferedSerial::~BufferedSerial()
{
}

BufferedSerial::baud(uint32_t bauds)
{
}

BufferedSerial::getc()
{
  if(this->loopqueue.empty())
    throw std::runtime_error("Trying to get character from empty queue");
  char c = this->loopqueue.front();
  this->loopqueue.pop();
  return c;
}

BufferedSerial::readable()
{
  return this->loopqueue.size();
}

BufferedSerial::write(void * data, uint32_t bufSize)
{
  char * caster = static_cast<char*>(data);

  for(uint32_t i = 0 ; i < bufSize ; i++)
    this->loopqueue.push(caster[i]);
}

BufferedSerial::writeable()
{
  return 1;
}
