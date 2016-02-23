// An executable file that generates two different test vectors
// shouldpass.md contains a dictionnary of datatype/topic/value -> frame
// that should be identified successfully by any distribution
// shoudlfail.md contains a set of non valid frames

#include "telemetry.h"
#include <queue>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

static std::queue<char> q;

// Not used. Don't care
int32_t read(void * buf, uint32_t sizeToRead)
{
  return 0;
}

// Not used. Don't care
int32_t readable()
{
  return 0;
}

int32_t write(void * buf, uint32_t sizeToWrite)
{
  char * caster = static_cast<char*>(buf);
  for(uint32_t i = 0 ; i < sizeToWrite ; i++)
  {
      q.push(caster[i]);
  }
}

int32_t writeable()
{
  return 1;
}

struct stringEntry
{
  std::string topic;
  std::string msg;
};


int main()
{
  TM_transport transport;

  transport.write = write;
  transport.read = read;
  transport.readable = readable;
  transport.writeable = writeable;

  init_telemetry(&transport);

  // Test vectors
  std::vector<stringEntry> pubchars;

  stringEntry s;

  s.topic = "foo" ; s.msg = "bar";
  pubchars.push_back(s);

  s.topic = "foo with spaces" ; s.msg = "ba a drs";
  pubchars.push_back(s);

  s.topic = "fo&6$^!" ; s.msg = ":/|wei_rdo";
  pubchars.push_back(s);

  // Output file
  std::ofstream myfile ("shouldpass.md");

  if(!myfile.is_open())
  {
    std::cerr << "Could not create a file for hosting tests vectors shouldpass.md" << std::endl;
    return -1;
  }

  //
  for(int i = 0 ; i < pubchars.size() ; i++)
  {
    publish(pubchars.at(i).topic.c_str(),pubchars.at(i).msg.c_str());

    myfile << "string" << '\t';
    myfile << pubchars.at(i).topic.c_str() << '\t';
    myfile << pubchars.at(i).msg.c_str() << '\t';

    while(!q.empty())
    {
      char c = q.front();
      myfile << c;
      q.pop();
    }
    myfile << std::endl;
  }
/*
  publish_u8(const char * topic, uint8_t msg);

  publish_u16(const char * topic, uint16_t msg);

  publish_u32(const char * topic, uint32_t msg);

  publish_i8(const char * topic, int8_t msg);

  publish_i16(const char * topic, int16_t msg);

  publish_i32(const char * topic, int32_t msg);

  publish_f32(const char * topic, float msg);
*/
  myfile.close();
  std::cout << "Test vector shouldpass generation success." << std::endl;
  return 0;
}
