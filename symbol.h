// symbol.h
#ifndef SYMBOL_H
#define SYMBOL_H

#include "hashtable.h"
#include <stdio.h>

extern HashTable *ht_symbol;

void constructor();

void addEntry(const char *symbol, int address);

int contains(const char *symbol);

int getAddress(const char *symbol);

void initSymbolTable();

#endif // SYMBOL_H