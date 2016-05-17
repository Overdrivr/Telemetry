#include "framing.h"

typedef enum _state
{
  IDLE, // No incoming frame is in process
  ESCAPING, // incoming frame in process, next character to be escaped
  ACTIVE // frame in process
} _state ;

typedef struct storage storage;
struct storage
{
   uint8_t * ptr;
   uint32_t size;
   uint32_t cursor;

};

static storage incomingStorage;
static storage outgoingStorage;

int8_t safe_append(storage * s, uint8_t byte);

static uint8_t SOF_;
static uint8_t EOF_;
static uint8_t ESC_;

static _state incoming_state;

void (*on_incoming_frame_cb)(uint8_t * storage, uint32_t occupiedSize);
void (*on_error_cb)(int32_t errCode);

void initialize_framing()
{
  incomingStorage.ptr = NULL;
  outgoingStorage.ptr = NULL;

  incomingStorage.size = 0;
  outgoingStorage.size = 0;

  incomingStorage.cursor = 0;
  incomingStorage.cursor = 0;

  SOF_ = 0xF7;
  EOF_ = 0x7F;
  ESC_ = 0x7D;

  incoming_state = IDLE;
}

void outgoing_storage(uint8_t * buf, uint32_t bufSize)
{
  outgoingStorage.ptr = buf;
  outgoingStorage.size = bufSize;
}

void begin()
{
  if(outgoingStorage.size == 0 || outgoingStorage.ptr == NULL)
    return;

  outgoingStorage.cursor = 0;

  // Should not fail
  safe_append(&outgoingStorage,SOF_);
}

void append(uint8_t byte)
{
  if(outgoingStorage.size == 0 || outgoingStorage.ptr == NULL)
    return;

  // byte == to flag, need to escape it
  if(byte == SOF_ || byte == EOF_ || byte == ESC_)
  {
    if(!safe_append(&outgoingStorage,ESC_))
      return;
  }

  if(!safe_append(&outgoingStorage,byte))
    return;
}

void append2(uint16_t twobytes)
{
  uint8_t * ptr = (uint8_t*)(&twobytes);
  append(ptr[0]);
  append(ptr[1]);
}

void append4(uint32_t fourbytes)
{
  uint8_t * ptr = (uint8_t*)(&fourbytes);
  append(ptr[0]);
  append(ptr[1]);
  append(ptr[2]);
  append(ptr[3]);
}

uint32_t end()
{
  if(outgoingStorage.size == 0 || outgoingStorage.ptr == NULL)
    return 0;

  if(!safe_append(&outgoingStorage,EOF_))
    return 0;

  return outgoingStorage.cursor;
}

void incoming_storage(uint8_t * buf, uint32_t bufSize)
{
  incomingStorage.ptr = buf;
  incomingStorage.size = bufSize;
}

void set_on_incoming_frame(void (*callback)(uint8_t * storage, uint32_t occupiedSize))
{
  on_incoming_frame_cb = callback;
}

void set_on_incoming_error(void (*callback)(int32_t errCode))
{
  on_error_cb = callback;
}

void feed(uint8_t byte)
{
  if(incomingStorage.size == 0 || incomingStorage.ptr == NULL)
    return;

  if(incoming_state == ESCAPING)
  {
    if(!safe_append(&incomingStorage,byte))
    {
      incoming_state = IDLE;
      return;
    }
    incoming_state = ACTIVE;
    return;
  }

  if(byte == SOF_)
  {
      incoming_state = ACTIVE;
      incomingStorage.cursor = 0;
      return;
  }

  if(incoming_state == ACTIVE)
  {
    if(byte == EOF_)
    {
        incoming_state = IDLE;
        on_incoming_frame_cb(incomingStorage.ptr, incomingStorage.cursor);
    }
    // Escape next character
    else if(byte == ESC_)
    {
        incoming_state = ESCAPING;
    }
    else
    {
      if(!safe_append(&incomingStorage,byte))
      {
        incoming_state = IDLE;
        return;
      }
      incoming_state = ACTIVE;
    }
  }
}

int8_t safe_append(storage * s, uint8_t byte)
{
  // Not enough space for 1 more character
  if(s->cursor + 1 >= s->size)
    return 0;

  s->ptr[s->cursor++] = byte;

  return 1;
}
