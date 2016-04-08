#ifndef TELEMETRY_DICTIONNARY_H_
#define TELEMETRY_DICTIONNARY_H_

#include "stdint.h"


enum ptr_type {
  ptr_f32 = 0,
  ptr_u8 = 1,
  ptr_u16 = 2,
  ptr_u32 = 3,
  ptr_i8 = 4,
  ptr_i16 = 5,
  ptr_i32 = 6,
  ptr_function = 8
};

typedef enum ptr_type ptr_type;

struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char * key;

    // Table can store for a given key all following pointers
    float     * ptr_f32;
    uint8_t   * ptr_u8;
    uint16_t  * ptr_u16;
    uint32_t  * ptr_u32;
    int8_t    * ptr_i8;
    int16_t   * ptr_i16;
    int32_t   * ptr_i32;
    void      * ptr_function;
};

#define HASHSIZE 101

void init_table(struct nlist ** hashtab);

/* lookup: look for s in hashtab */
struct nlist * lookup(struct nlist ** hashtab, const char * key);

struct nlist * install(struct nlist ** hashtab, const char * key, void * ptr, ptr_type type);

#endif
