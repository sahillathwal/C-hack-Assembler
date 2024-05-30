#include "symbol.h"

HashTable *ht_symbol; // Define ht_symbol

// function to Creates a new empty symbol table.
void constructor()
{
    ht_symbol = createHashTable(100); // Create a new hash table with size 100
}

// function to Adds the pair (symbol, address) to the table.
void addEntry(const char *symbol, int address)
{
    char value[10];                   // Create a buffer to store the address as a string
    sprintf(value, "%d", address);    // Convert the address to a string
    insert(ht_symbol, symbol, value); // Insert the symbol and address into the hash table
}

// function to Returns true if the symbol table contains the given symbol.
int contains(const char *symbol)
{
    return get(ht_symbol, symbol) != NULL; // Check if the symbol is in the hash table
}

// function to Returns the address associated with the symbol.
int getAddress(const char *symbol)
{
    char *value = get(ht_symbol, symbol); // Get the address associated with the symbol
    if (value == NULL)
    {
        return -1; // Return -1 if the symbol is not found
    }
    return atoi(value); // Convert the address string to an integer and return it
}

// Initialize the symbol table with all the predefined symbols and their pre-allocated RAM addresses
void initSymbolTable()
{
    addEntry("SP", 0);
    addEntry("LCL", 1);
    addEntry("ARG", 2);
    addEntry("THIS", 3);
    addEntry("THAT", 4);
    addEntry("R0", 0);
    addEntry("R1", 1);
    addEntry("R2", 2);
    addEntry("R3", 3);
    addEntry("R4", 4);
    addEntry("R5", 5);
    addEntry("R6", 6);
    addEntry("R7", 7);
    addEntry("R8", 8);
    addEntry("R9", 9);
    addEntry("R10", 10);
    addEntry("R11", 11);
    addEntry("R12", 12);
    addEntry("R13", 13);
    addEntry("R14", 14);
    addEntry("R15", 15);
    addEntry("SCREEN", 16384);
    addEntry("KBD", 24576);
}