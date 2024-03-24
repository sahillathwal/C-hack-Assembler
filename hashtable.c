#include "hashtable.h"

// Function to calculate the hash of a key
int hash(const char *key)
{
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash += key[i];
    }
    return hash % TABLE_SIZE; // Return the hash modulo the table size to ensure it falls within the table range
}

// Function to create a new hash table
HashTable *createHashTable()
{
    HashTable *hashTable = malloc(sizeof(HashTable));             // allocating memory for the hash table
    hashTable->entries = calloc(TABLE_SIZE, sizeof(HashEntry *)); // allocating memory for the entries in the hash table
    return hashTable;
}

// Function to insert a key-value pair into the hash table
void insert(HashTable *hashTable, const char *key, char *value)
{
    int index = hash(key); // Calculate the hash of the key

    // Create a new entry
    HashEntry *newEntry = malloc(sizeof(HashEntry)); // Allocate memory for the new entry
    newEntry->key = strdup(key);                     // Copy the key to the new entry
    newEntry->value = strdup(value);                 // Copy the value to the new entry

    // Insert into the hash table
    hashTable->entries[index] = newEntry;
}

// Function to get the value associated with a key from the hash table
char *get(HashTable *hashTable, const char *key)
{
    int index = hash(key); // Calculate the hash of the key

    // Retrieve the entry at the calculated index
    HashEntry *entry = hashTable->entries[index];

    // If entry is NULL or key does not match, return a default value (e.g., -1)
    if (entry == NULL || strcmp(entry->key, key) != 0)
    {
        return NULL;
    }

    // Return the value associated with the key
    return entry->value;
}
