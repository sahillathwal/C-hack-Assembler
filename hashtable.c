#include "hashtable.h"

// Function to calculate the hash of a key
int hash(HashTable *hashTable, const char *key)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *key++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % hashTable->size; // Return the hash modulo the table size to ensure it falls within the table range
}

// Function to create a new hash table
HashTable *createHashTable(int size)
{
    HashTable *hashTable = malloc(sizeof(HashTable));       // allocating memory for the hash table
    hashTable->size = size;                                 // setting the size of the hash table
    hashTable->entries = calloc(size, sizeof(HashEntry *)); // allocating memory for the entries in the hash table
    return hashTable;
}

// Function to insert a key-value pair into the hash table
void insert(HashTable *hashTable, const char *key, char *value)
{
    int index = hash(hashTable, key); // Calculate the hash of the key

    // Create a new entry
    HashEntry *newEntry = malloc(sizeof(HashEntry)); // Allocate memory for the new entry
    newEntry->key = strdup(key);                     // Copy the key to the new entry
    newEntry->value = strdup(value);                 // Copy the value to the new entry
    newEntry->next = NULL;                           // Initialize the next pointer to NULL

    // If the bucket is empty, assign the new entry to it
    if (hashTable->entries[index] == NULL)
    {
        hashTable->entries[index] = newEntry;
    }
    else
    {
        // If the bucket is not empty, add the new entry to the end of the list
        HashEntry *currentEntry = hashTable->entries[index];
        while (currentEntry->next != NULL)
        {
            currentEntry = currentEntry->next;
        }
        currentEntry->next = newEntry;
    }
}

// Function to get the value associated with a key from the hash table
char *get(HashTable *hashTable, const char *key)
{
    int index = hash(hashTable, key); // Calculate the hash of the key

    // Retrieve the entry at the calculated index
    HashEntry *entry = hashTable->entries[index];

    // Traverse the linked list to find the matching key
    while (entry != NULL)
    {
        if (strcmp(entry->key, key) == 0)
        {
            // Return the value associated with the key
            return entry->value;
        }
        entry = entry->next;
    }

    // If no matching key is found, return NULL
    return NULL;
}
