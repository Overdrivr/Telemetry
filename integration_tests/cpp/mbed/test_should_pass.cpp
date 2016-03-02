#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "telemetry_config.h"
#ifdef TELEMETRY_ARDUINO_DISTRIBUTION
#include "Telemetry.h"
#else
#include "Telemetry.hpp"
#endif
#include <fstream>
#include <sstream>
#include <iostream>

static std::string topic;
static std::string frametype;
static std::string message;
static uint8_t payload_u8;
static uint16_t payload_u16;
static uint32_t payload_u32;
static int8_t payload_i8;
static int16_t payload_i16;
static int32_t payload_i32;
static float payload_f32;

void process(TM_state * state, TM_msg * msg);

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

        if(entry.size() == 0)
        {
            INFO("Test complete");
            break;
        }

        frametype = entry.substr(0, entry.find(delimiter));
        entry.erase(0, entry.find(delimiter) + delimiter.length());

        topic = entry.substr(0, entry.find(delimiter));
        entry.erase(0, entry.find(delimiter) + delimiter.length());


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

        REQUIRE(frame.size() == 0);

        INFO("Testing vector conversion finished");

        if(frametype == "string")
        {
            tm.pub(topic.c_str(),message.c_str());
        }
        else if(frametype == "u8")
        {
            // convert message to u8
            payload_u8 = strtoul(message.data(),NULL,10);
            //std::cout << "payload "<< static_cast<int>(payload_u8) << std::endl;
            tm.pub_u8(topic.c_str(),payload_u8);
        }
        else if(frametype == "u16")
        {
            payload_u16 = strtoul(message.data(),NULL,10);
            tm.pub_u16(topic.c_str(),payload_u16);
        }
        else if(frametype == "u32")
        {
            payload_u32 = strtoul(message.data(),NULL,10);
            tm.pub_u32(topic.c_str(),payload_u32);
        }
        else if(frametype == "i8")
        {
            payload_i8 = strtol(message.data(),NULL,10);
            //std::cout<<"Payload i8 : " << static_cast<int>(payload_i8)<<std::endl;
            tm.pub_i8(topic.c_str(),payload_i8);
        }
        else if(frametype == "i16")
        {
            payload_i16 = strtol(message.data(),NULL,10);
            tm.pub_i16(topic.c_str(),payload_i16);
        }
        else if(frametype == "i32")
        {
            payload_i32 = strtol(message.data(),NULL,10);
            tm.pub_i32(topic.c_str(),payload_i32);
        }
        else if(frametype == "f32")
        {
            payload_f32 = strtof(message.data(),NULL);
            tm.pub_f32(topic.c_str(),payload_f32);
        }
        else
        {
          FAIL("Frametype " << frametype << " not supported yet");
        }

        int32_t bytesWritten = mockTransport->readable();

        rawserialdata.clear();

        for(size_t i = 0 ; i < expecteddata.size() ; ++i)
        {
          uint8_t c;
          mockTransport->read(&c,1);
          rawserialdata.push_back(c);

          char buffer[10];
          sprintf(buffer, "%02x", c);

          INFO("Compared byte["<<i<<"]"<< buffer << " vs " << expecteddata.at(i));

          REQUIRE(strcmp(expecteddata.at(i).c_str(),buffer) == 0);
        }

        REQUIRE(bytesWritten > 0);
        REQUIRE(bytesWritten == expecteddata.size());

        // Restore read bytes into buffer
        for(size_t i = 0 ; i < rawserialdata.size() ; ++i)
        {
          uint8_t c = rawserialdata.at(i);
          mockTransport->write(&c, 1);
        }

        // Check frame matches expected in process function
        tm.update();
        // After update, nothing should be left inside transport
        REQUIRE(mockTransport->readable() == 0);

    }
    valid_vectors.close();
}


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
  else if(frametype == "u8")
  {
    REQUIRE(msg->type == TM_uint8);

    std::string curtopic(msg->topic);
    REQUIRE(curtopic == topic);

    uint8_t curpayload;
    uint32_t ret = emplace_u8(msg, &curpayload);

    REQUIRE(ret == 1);
    REQUIRE(ret);
    REQUIRE(curpayload == payload_u8);
  }
  else if(frametype == "u16")
  {
    REQUIRE(msg->type == TM_uint16);

    std::string curtopic(msg->topic);
    REQUIRE(curtopic == topic);

    uint16_t curpayload;
    uint32_t ret = emplace_u16(msg, &curpayload);

    REQUIRE(ret == 1);
    REQUIRE(ret);
    REQUIRE(curpayload == payload_u16);
  }
  else if(frametype == "u32")
  {
    REQUIRE(msg->type == TM_uint32);

    std::string curtopic(msg->topic);
    REQUIRE(curtopic == topic);

    uint32_t curpayload;
    uint32_t ret = emplace_u32(msg, &curpayload);

    REQUIRE(ret == 1);
    REQUIRE(ret);
    REQUIRE(curpayload == payload_u32);
  }
  else if(frametype == "i8")
  {
    REQUIRE(msg->type == TM_int8);

    std::string curtopic(msg->topic);
    REQUIRE(curtopic == topic);

    int8_t curpayload;
    uint32_t ret = emplace_i8(msg, &curpayload);

    REQUIRE(ret == 1);
    REQUIRE(ret);
    REQUIRE(curpayload == payload_i8);
  }
  else if(frametype == "i16")
  {
    REQUIRE(msg->type == TM_int16);

    std::string curtopic(msg->topic);
    REQUIRE(curtopic == topic);

    int16_t curpayload;
    uint32_t ret = emplace_i16(msg, &curpayload);

    REQUIRE(ret == 1);
    REQUIRE(ret);
    REQUIRE(curpayload == payload_i16);
  }
  else if(frametype == "i32")
  {
    REQUIRE(msg->type == TM_int32);

    std::string curtopic(msg->topic);
    REQUIRE(curtopic == topic);

    int32_t curpayload;
    uint32_t ret = emplace_i32(msg, &curpayload);

    REQUIRE(ret == 1);
    REQUIRE(ret);
    REQUIRE(curpayload == payload_i32);
  }
  else if(frametype == "f32")
  {
    REQUIRE(msg->type == TM_float32);

    std::string curtopic(msg->topic);
    REQUIRE(curtopic == topic);

    float curpayload;
    uint32_t ret = emplace_f32(msg, &curpayload);

    REQUIRE(ret == 1);
    REQUIRE(ret);
    REQUIRE(curpayload == payload_f32);
  }
  else
  {
    FAIL("Frametype not testable : "<< frametype);
  }
}
