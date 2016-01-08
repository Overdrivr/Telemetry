#ifndef TELEMETRY_H_
#define TELEMETRY_H_

#include "stddef.h"
#include "stdint.h"

// Forward declaration of user state
typedef struct TM_state TM_state;

// Enumeration of supported message payloads
enum TM_type {
  TM_float32,
  TM_uint8,
  TM_uint16,
  TM_uint32,
  TM_int8,
  TM_int16,
  TM_int32
};
typedef enum TM_type TM_type;

// Data structure for received messages
typedef struct TM_msg TM_msg;
struct TM_msg {
  TM_type type;
  void * buffer;
};

TM_state * statePtr;

void initTelemetry(TM_state* s);

// Decodes TM_msg buffer and emplaces its value into dst
// Returns 0 if decoding was successful
int emplace(TM_msg* m, char     * buf, size_t bufSize);
int emplace_u8(TM_msg* m, uint8_t  * dst);
int emplace_u16(TM_msg* m, uint16_t * dst);
int emplace_u32(TM_msg* m, uint32_t * dst);
int emplace_i8(TM_msg* m, int8_t   * dst);
int emplace_i16(TM_msg* m, int16_t  * dst);
int emplace_i32(TM_msg* m, int32_t  * dst);
int emplace_f32(TM_msg* m, float    * dst);

void publish(const char * topic, char *   msg);
void publish_u8(const char * topic, uint8_t  msg);
void publish_u16(const char * topic, uint16_t msg);
void publish_u32(const char * topic, uint32_t msg);
void publish_i8(const char * topic, int8_t   msg);
void publish_i16(const char * topic, int16_t  msg);
void publish_i32(const char * topic, int32_t  msg);
void publish_f32(const char * topic, float    msg);

void subscribe(char * topic, void (*callback)(TM_state* s, TM_msg* m));

void updateTelemetry(float elapsedTime);

#endif
