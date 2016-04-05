// From Section 6.6 of the "C Programming Language" by Brian W. Kernighan (ISBN-13: 978-0131103627)

#ifndef TELEMETRY_DICTIONNARY_H_
#define TELEMETRY_DICTIONNARY_H_

struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

#define HASHSIZE 101
static struct nlist * hashtab[HASHSIZE]; /* pointer table */

/* lookup: look for s in hashtab */
struct nlist * lookup(char *s);

/* install: put (name, defn) in hashtab */
struct nlist * install(char *name, char *defn);

#endif
