#include "dictionnary.h"
#include "stdlib.h"
#include "stdint.h"

/* hash: form hash value for string s */
unsigned hash(char * s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

char *strdup(char * s) /* make a duplicate of s */
{
    char *p;
    p = (char *) malloc(strlen(s)+1); /* +1 for ’\0’ */
    if (p != NULL)
       strcpy(p, s);
    return p;
}

void init_entry(struct nlist * entry)
{
  entry->ptr_f32 = NULL;
  entry->ptr_u8 = NULL;
  entry->ptr_u16 = NULL;
  entry->ptr_u32 = NULL;
  entry->ptr_i8 = NULL;
  entry->ptr_i16 = NULL;
  entry->ptr_i32 = NULL;
  entry->ptr_callback = NULL;
}

void init_table(struct nlist ** hashtab)
{
  uint32_t i = 0;
  for(i = 0 ; i < HASHSIZE ; i++)
  {
    hashtab[i] = NULL;
  }
}

/* lookup: look for s in hashtab */
struct nlist *lookup(struct nlist ** hashtab, char * key)
{
    struct nlist *np;

    for (np = hashtab[hash(key)]; np != NULL; np = np->next)
    {
      if (strcmp(key, np->key) == 0)
      {
        return np; /* found */
      }
    }
    return NULL; /* not found */
}

struct nlist * install(struct nlist ** hashtab, char * key, void * ptr, ptr_type type)
{
    struct nlist * np;
    unsigned hashval;

    if ((np = lookup(hashtab, key)) == NULL)
    {
        // Allocate new hastable entry and initialize it
        np = (struct nlist *) malloc(sizeof(*np));

        // If allocation failed
        if (np == NULL || (np->key = strdup(key)) == NULL)
          return NULL;

        init_entry(np);

        hashval = hash(key);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }

    // Set value
    switch(type)
    {
        case ptr_float32:
          np->ptr_f32 = (float *)(ptr);
          break;
    }

    return np;
}
