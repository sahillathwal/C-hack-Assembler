// hashtable.h

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <string.h>

extern int TABLE_SIZE;

// Define a structure for the hash table entry
typedef struct
{
    char *key;
    char *value;
} HashEntry;

// Define a structure for the hash table itself
typedef struct
{
    HashEntry **entries;
} HashTable;

// Function prototypes
HashTable *createHashTable();
void insert(HashTable *hashTable, const char *key, char *value);
char *get(HashTable *hashTable, const char *key);

#endif // HASHTABLE_H