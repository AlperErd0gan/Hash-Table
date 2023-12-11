#ifndef HASH_H
#define HASH_H

typedef struct Key {
    char *word;
    unsigned long count;
    struct Key *next;
} Key;

unsigned long hash_compute(const char *str);
Key **hash_create_table(void);
Key *hash_lookup(Key **table, const char *str, int create);
void hash_free(Key **table);
void hash_dump(Key **table, int n);

#endif  // HASH_H

