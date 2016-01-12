#ifndef FRAMING_H_
#define FRAMING_H_

#include "stddef.h"
#include "stdint.h"

void initialize_framing();
// Outgoing data
// Set storage for the outgoing frame
void outgoing_storage(uint8_t * buf, uint32_t bufSize);

void begin();
void append(uint8_t byte);
void append2(uint16_t twobytes);
void append4(uint32_t fourbytes);
uint32_t end();

// Incoming data
// Set storage for the incoming data
void incoming_storage(uint8_t * buf, uint32_t bufSize);

void set_on_incoming_frame(void (*callback)(uint8_t * storage, uint32_t occupiedSize));
void set_on_incoming_error(void (*callback)(int32_t errCode));
void feed(uint8_t byte);
#endif
