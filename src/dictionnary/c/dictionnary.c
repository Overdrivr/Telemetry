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

void init_table(struct nlist ** hashtab)
{
  uint32_t i = 0;
  for(i = 0 ; i < HASHSIZE ; i++)
  {
    hashtab[i] = NULL;
  }
}

/* lookup: look for s in hashtab */
struct nlist *lookup(struct nlist ** hashtab, char * s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    {
      if (strcmp(s, np->name) == 0)
      {
        return np; /* found */
      }
    }
    return NULL; /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(struct nlist ** hashtab, char * name, char * defn)
{
    struct nlist * np;
    unsigned hashval;

    if ((np = lookup(hashtab, name)) == NULL)
    {
        np = (struct nlist *) malloc(sizeof(*np));

        if (np == NULL || (np->name = strdup(name)) == NULL)
          return NULL;

        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else
        free((void *) np->defn); /*free previous defn */

    if ((np->defn = strdup(defn)) == NULL)
       return NULL;

    return np;
}
