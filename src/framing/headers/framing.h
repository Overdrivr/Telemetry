#ifndef FRAMING_H_
#define FRAMING_H_

// Outgoing data
// Set storage for the outgoing frame
void outgoing_storage(void * buf, uint32_t bufSize);

void start();
void append(char c);
void end();

// Incoming data
// Set storage for the incoming data
void incoming_storage(void * buf, uint32_t bufSize);

void set_on_incoming_frame(void (*callback)(void * storage, uint32_t occupiedSize));
void set_on_incoming_error(void (*callback)(int32_t errCode));
void feed(char c);
#endif
