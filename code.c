#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"

HashTable *ht_dest;
HashTable *ht_comp;
HashTable *ht_jump;

// creates a new hashtable and fills it with the dest mnemonic and its binary code
void createDestTable()
{
    ht_dest = createHashTable(8);
    insert(ht_dest, "null", "000");
    insert(ht_dest, "M", "001");
    insert(ht_dest, "D", "010");
    insert(ht_dest, "MD", "011");
    insert(ht_dest, "A", "100");
    insert(ht_dest, "AM", "101");
    insert(ht_dest, "AD", "110");
    insert(ht_dest, "AMD", "111");
}

// creates a new hashtable and fills it with the comp mnemonic and its binary code
void createCompTable()
{
    ht_comp = createHashTable(28);
    insert(ht_comp, "0", "0101010");
    insert(ht_comp, "1", "0111111");
    insert(ht_comp, "-1", "0111010");
    insert(ht_comp, "D", "0001100");
    insert(ht_comp, "A", "0110000");
    insert(ht_comp, "!D", "0001101");
    insert(ht_comp, "!A", "0110001");
    insert(ht_comp, "-D", "0001111");
    insert(ht_comp, "-A", "0110011");
    insert(ht_comp, "D+1", "0011111");
    insert(ht_comp, "A+1", "0110111");
    insert(ht_comp, "D-1", "0001110");
    insert(ht_comp, "A-1", "0110010");
    insert(ht_comp, "D+A", "0000010");
    insert(ht_comp, "D-A", "0010011");
    insert(ht_comp, "A-D", "0000111");
    insert(ht_comp, "D&A", "0000000");
    insert(ht_comp, "D|A", "0010101");
    insert(ht_comp, "M", "1110000");
    insert(ht_comp, "!M", "1110001");
    insert(ht_comp, "-M", "1110011");
    insert(ht_comp, "M+1", "1110111");
    insert(ht_comp, "M-1", "1110010");
    insert(ht_comp, "D+M", "1000010");
    insert(ht_comp, "D-M", "1010011");
    insert(ht_comp, "M-D", "1000111");
    insert(ht_comp, "D&M", "1000000");
    insert(ht_comp, "D|M", "1010101");
}

// creates a new hashtable and fills it with the jump mnemonic and its binary code
void createJumpTable()
{
    ht_jump = createHashTable(8);
    insert(ht_jump, "null", "000");
    insert(ht_jump, "JGT", "001");
    insert(ht_jump, "JEQ", "010");
    insert(ht_jump, "JGE", "011");
    insert(ht_jump, "JLT", "100");
    insert(ht_jump, "JNE", "101");
    insert(ht_jump, "JLE", "110");
    insert(ht_jump, "JMP", "111");
}

// creates the code tables
void createCodeTables()
{
    createDestTable();
    createCompTable();
    createJumpTable();
}

char *destCode(char *dest)
{
    // returns the binary code of the dest mnemonic
    char *result = get(ht_dest, dest);
    if (result == NULL)
    {
        // return a default value or handle the error appropriately
        return "000";
    }
    return result;
}

char *compCode(char *comp)
{
    // returns the binary code of the comp mnemonic
    char *result = get(ht_comp, comp);
    if (result == NULL)
    {
        // return a default value or handle the error appropriately
        return "0000000";
    }
    return result;
}

char *jumpCode(char *jump)
{
    // returns the binary code of the jump mnemonic
    return get(ht_jump, jump);
}

// void testDestCode()
// {
//     char *destMnemonics[] = {"null", "M", "D", "MD", "A", "AM", "AD", "AMD"};
//     int numMnemonics = sizeof(destMnemonics) / sizeof(destMnemonics[0]);

//     for (int i = 0; i < numMnemonics; i++)
//     {
//         char *mnemonic = destMnemonics[i];
//         char *binaryCode = destCode(mnemonic);
//         printf("destCode('%s') = '%s'\n", mnemonic, binaryCode);
//     }
// }

// int main()
// {
//     createCodeTables();
//     testDestCode();
//     return 0;
// }