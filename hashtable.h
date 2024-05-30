// hashtable.h

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <string.h>

// Define a structure for the hash table entry
typedef struct HashEntry
{
    char *key;
    char *value;
    struct HashEntry *next;
} HashEntry;

// Define a structure for the hash table itself
typedef struct
{
    int size;
    HashEntry **entries;
} HashTable;

// Function prototypes
HashTable *createHashTable(int size);
void insert(HashTable *hashTable, const char *key, char *value);
char *get(HashTable *hashTable, const char *key);
void freeHashTable(HashTable *hashTable);

void printSortedHashTable(HashTable *hashTable);

#endif // HASHTABLE_H