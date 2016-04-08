#ifndef TELEMETRY_UTILS_H_
#define TELEMETRY_UTILS_H_

#include "stddef.h"
#include "stdint.h"
#include "string.h"

// Forward declaration of user state
typedef struct TM_state TM_state;

// Enumeration of supported message payloads
enum TM_type {
  TM_float32 = 0,
  TM_uint8 = 1,
  TM_uint16 = 2,
  TM_uint32 = 3,
  TM_int8 = 4,
  TM_int16 = 5,
  TM_int32 = 6,
  TM_string = 7
};

typedef enum TM_type TM_type;


// Data structure for received messages
typedef struct TM_msg TM_msg;
struct TM_msg {
  TM_type type;
  char * topic;
  void * buffer;
  uint32_t size;
};

// Data structure for holding transport interface
typedef struct TM_transport TM_transport;
struct TM_transport {
  int32_t (*read)(uint8_t * buf, uint32_t sizeToRead);
  int32_t (*readable)();
  int32_t (*write)(uint8_t * buf, uint32_t sizeToWrite);
  int32_t (*writeable)();
};

// Decodes TM_msg buffer and emplaces its value into dst
// Returns 1 (true) if decoding was successful
uint32_t emplace(TM_msg * m, char * buf, size_t bufSize);
uint32_t emplace_u8(TM_msg * m, uint8_t * dst);
uint32_t emplace_u16(TM_msg * m, uint16_t * dst);
uint32_t emplace_u32(TM_msg * m, uint32_t * dst);
uint32_t emplace_i8(TM_msg * m, int8_t * dst);
uint32_t emplace_i16(TM_msg * m, int16_t * dst);
uint32_t emplace_i32(TM_msg * m, int32_t * dst);
uint32_t emplace_f32(TM_msg * m, float * dst);

// Returns 1 if topicToMatch matches m->topic
//         0 otherwise
uint32_t match(TM_msg * m, const char * topicToMatch);

// Returns 1 if topicToMatch matches m->topic and typeToMatch matches m->type,
//         0 otherwise
uint32_t fullmatch(TM_msg * m, const char * topicToMatch, TM_type typeToMatch);

// Decodes TM_msg buffer and update its value into dst if matching topic
// Returns 1 (true) if decoding was successful
uint32_t update(TM_msg * msg, const char *topic, char *var, size_t bufSize);
uint32_t update_u8(TM_msg * msg, const char *topic, uint8_t *var);
uint32_t update_u16(TM_msg * msg, const char *topic, uint16_t *var);
uint32_t update_u32(TM_msg * msg, const char *topic, uint32_t *var);
uint32_t update_i8(TM_msg * msg, const char *topic, int8_t *var);
uint32_t update_i16(TM_msg * msg, const char *topic, int16_t *var);
uint32_t update_i32(TM_msg * msg, const char *topic, int32_t *var);
uint32_t update_f32(TM_msg * msg, const char *topic, float *var);


#endif
