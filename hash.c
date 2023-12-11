#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"

// Constants specific to the implementation
#define MULTIPLIER 29
#define MAXBUCKETS 100

unsigned long hash_compute(const char *str)
{
    if (str == NULL)
    {
        return 0;
    }

    unsigned long hash = 0;
    while (*str != '\0')
    {
        hash += *str;
        str++;
    }
    return hash % MAXBUCKETS;
}

Key **hash_create_table(void)
{
    Key **table = (Key **)malloc(MAXBUCKETS * sizeof(Key *));
    if (table == NULL)
    {
        fprintf(stderr, "Memory allocation failed for the hash table.\n");
        exit(EXIT_FAILURE);
    }

    for (long int i = 0; i < MAXBUCKETS; i++)
    {
        table[i] = NULL;
    }

    return table;
}

Key *hash_lookup(Key **table, const char *str, int create) {
    int hash_index = hash_compute(str);

    if (hash_index < 0) {
        hash_index = -hash_index;
    }

    Key *current = table[hash_index];
    while (current != NULL) {
        if (strcmp(current->word, str) == 0) {
            // Word found, increment count
            current->count++;
            return current;
        }

        current = current->next;
    }

    if (create) {
        Key *newKey = (Key *)malloc(sizeof(Key));
        if (newKey == NULL) {
            return NULL;
        }

        newKey->word = (char *)malloc(strlen(str) + 1);
        if (newKey->word == NULL) {
            free(newKey);
            return NULL;
        }

        strcpy(newKey->word, str);
        newKey->count = 1;

        newKey->next = table[hash_index];
        table[hash_index] = newKey;

        return newKey;
    }

    return NULL;
}

void hash_free(Key **table)
{
    if (table == NULL)
    {
        return;
    }

    for (long int i = 0; i < MAXBUCKETS; i++)
    {
        Key *current = table[i];
        while (current != NULL)
        {
            Key *temp = current;
            current = current->next;

            if (temp->word != NULL)
            {
                free(temp->word);
            }
            free(temp);
        }
        table[i] = NULL;
    }

    free(table);
}

void hash_dump(Key **table, int n)
{
    if (table == NULL)
    {
        return;
    }

    for (long int i = 0; i < MAXBUCKETS; i++)
    {
        Key *current = table[i];
        while (current != NULL)
        {
            if (current->word != NULL && current->count >= n)
            {
                printf("%30s-->%5ld\n", current->word, current->count);
            }
            current = current->next;
        }
    }
}

