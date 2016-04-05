#ifndef TELEMETRY_DICTIONNARY_H_
#define TELEMETRY_DICTIONNARY_H_

struct nlist { /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name; /* defined name */
    char *defn; /* replacement text */
};

#define HASHSIZE 101

void init_table(struct nlist ** hashtab);

/* lookup: look for s in hashtab */
struct nlist * lookup(struct nlist ** hashtab, char *s);

/* install: put (name, defn) in hashtab */
struct nlist * install(struct nlist ** hashtab, char *name, char *defn);

#endif
