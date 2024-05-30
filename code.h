#ifndef CODE_H
#define CODE_H

#include "hashtable.h"

extern HashTable *ht_dest;
extern HashTable *ht_comp;
extern HashTable *ht_jump;

void createCodeTables();

char *destCode(char *dest);
char *compCode(char *comp);
char *jumpCode(char *jump);

#endif // CODE_H