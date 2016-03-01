#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Telemetry.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

static std::string topic;
static std::string frametype;
static std::string message;

void process(TM_state * state, TM_msg * msg)
{
  if(frametype == "string")
  {
    REQUIRE(msg->type == TM_string);

    std::string curtopic(msg->topic);
    REQUIRE(curtopic == topic);

    char curmessage[512];
    uint32_t ret = emplace(msg, curmessage, 512);
    std::string curmessagestr(curmessage);

    REQUIRE(ret == 1);
    REQUIRE(ret);
    REQUIRE(curmessagestr == message);
  }
}

struct TM_state {
  uint8_t dummy;
};

TEST_CASE( "Valid vectors test") {
    std::ifstream valid_vectors;
    valid_vectors.open("valid_vectors.csv", std::ifstream::in);

    REQUIRE(valid_vectors.is_open());

    INFO("Test file loaded.")

    Telemetry tm;
    TM_state state;
    TM_transport * mockTransport = tm.get_transport();
    tm.sub(process, &state);

    std::string delimiter = "\t;\t";

    std::vector<std::string> expecteddata;
    std::vector<uint8_t> rawserialdata;

    while(valid_vectors.good())
    {
      std::string entry;
      std::getline(valid_vectors,entry);

      frametype = entry.substr(0, entry.find(delimiter));
      entry.erase(0, entry.find(delimiter) + delimiter.length());

      topic = entry.substr(0, entry.find(delimiter));
      entry.erase(0, entry.find(delimiter) + delimiter.length());

      if(frametype == "string")
      {
          message = entry.substr(0, entry.find(delimiter));
          entry.erase(0, entry.find(delimiter) + delimiter.length());

          std::string frame = entry.substr(0, entry.find(delimiter));
          entry.erase(0, entry.find(delimiter) + delimiter.length());

          INFO("Testing vector :" << frametype << " | "<< topic << " : " << message << " | " << frame);

          expecteddata.clear();

          while(frame.size() > 1)
          {
            std::string sub = frame.substr(0, 2);
            expecteddata.push_back(sub);
            //std::cout<<"Data : "<<sub<<std::endl;
            frame.erase(0, 2);
          }

          INFO("Testing vector conversion finished");

          // 2 hex characters for 1 byte
          size_t frameSize = expecteddata.size();

          tm.pub(topic.c_str(),message.c_str());

          int32_t bytesWritten = mockTransport->readable();

          REQUIRE(bytesWritten > 0);
          REQUIRE(bytesWritten == frameSize);

          rawserialdata.clear();

          for(size_t i = 0 ; i < expecteddata.size() ; ++i)
          {
            uint8_t c;
            mockTransport->read(&c,1);
            rawserialdata.push_back(c);

            char buffer[10];
            sprintf(buffer, "%02x", c);

            INFO("Compared " << buffer << " vs " << expecteddata.at(i));

            REQUIRE(strcmp(expecteddata.at(i).c_str(),buffer) == 0);
          }

          // Restore read bytes into buffer
          for(size_t i = 0 ; i < rawserialdata.size() ; ++i)
          {
            uint8_t c = rawserialdata.at(i);
            mockTransport->write(&c, 1);
          }

          // Check frame matches expected in process function
          tm.update();
      }
      else
      {
          //REQUIRE(0 == 1);
      }
    }

    valid_vectors.close();
}
