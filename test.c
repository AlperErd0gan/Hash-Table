#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

int main()
{
    // Create a hash table
    Key **table = hash_create_table();

    // Test data with different words and counts
    const char *words[] = {"apple", "banana", "orange", "apple", "grape", "kiwi", "kiwi", "strawberry", "banana", "kiwi",
                           "pineapple", "pear", "watermelon", "blueberry", "mango", "kiwi", "kiwi", "strawberry", "banana", "kiwi"};

    printf("Inserting words into the hash table...\n");

    // Insert words into the hash table
    for (int i = 0; i < sizeof(words) / sizeof(words[0]); i++)
    {
        Key *result = hash_lookup(table, words[i], 1);
        if (result != NULL)
        {
            printf("%-20s | Count: %-3ld | Hash Index: %-3lu\n", result->word, result->count, hash_compute(words[i]));

        }
        else
        {
            printf("Failed to insert word: %s\n", words[i]);
        }
    }

    printf("\nPrinting words with count >= 2...\n");

    // Print words with count >= 2
    hash_dump(table, 2);

    printf("\nFreeing the hash table...\n");

    // Free the hash table
    hash_free(table);

    return 0;
}
