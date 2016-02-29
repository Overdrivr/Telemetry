#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "Telemetry.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

void process(TM_state * state, TM_msg * msg)
{

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

    std::vector<std::string> serialdata;

    while(valid_vectors.good())
    {
      std::string entry;
      std::getline(valid_vectors,entry);

      std::string frametype = entry.substr(0, entry.find(delimiter));
      entry.erase(0, entry.find(delimiter) + delimiter.length());

      std::string topic = entry.substr(0, entry.find(delimiter));
      entry.erase(0, entry.find(delimiter) + delimiter.length());

      if(frametype == "string")
      {
          std::string message = entry.substr(0, entry.find(delimiter));
          entry.erase(0, entry.find(delimiter) + delimiter.length());

          std::string frame = entry.substr(0, entry.find(delimiter));
          entry.erase(0, entry.find(delimiter) + delimiter.length());

          INFO("Testing vector :" << frametype << " | "<< topic << " : " << message << " | " << frame);

          serialdata.clear();

          while(frame.size() > 1)
          {
            std::string sub = frame.substr(0, 2);
            serialdata.push_back(sub);
            std::cout<<"Data : "<<sub<<std::endl;
            frame.erase(0, 2);
          }

          INFO("Testing vector conversion finished");

          // 2 hex characters for 1 byte
          size_t frameSize = serialdata.size();

          tm.pub(topic.c_str(),message.c_str());

          int32_t bytesWritten = mockTransport->readable();

          REQUIRE(bytesWritten > 0);
          REQUIRE(bytesWritten == frameSize);

          for(size_t i = 0 ; i < serialdata.size() ; ++i)
          {
            uint8_t c;
            mockTransport->read(&c,1);

            char buffer[10];
            sprintf(buffer, "%02x", c);

            INFO("Compared " << buffer << " vs " << serialdata.at(i));

            REQUIRE(strcmp(serialdata.at(i).c_str(),buffer) == 0);
          }

          tm.update();

          // Check frame matches expected in process
      }
      else
      {
          //REQUIRE(0 == 1);
      }
    }

    valid_vectors.close();
}
