#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// varabile to store the file arrgument provided by user
char *input_file;

// FILE pointer to store the file pointer created by initializer function
FILE *file_pointer;

// varaible to store cuurent command
char *current_command;

// varaible to store command type
char *command_type;

int is_ok = EXIT_FAILURE;

// Opens the input file/stream for parsing and stores the file pointer to file_pointer.
int initializerParser(char *input_file)
{
    file_pointer = fopen(input_file, "r");

    // check if file opening failed
    if (!file_pointer)
    {
        perror("File opening failed");
        return is_ok;
    }
}

// function to check if there are more commands left in the input file
bool hasMoreCommandsParser()
{
    // if the end of the stream has not been reached feof returns zero; hence ture_false gets assgined false
    bool ture_false = (feof(file_pointer) == 0) ? true : false;

    // returns false value if end of file has been reached else returns ture
    return ture_false;
}

// Reads the next command from the input and makes it the current command.
void advanceParser()
{
    // stores the current command to current_command
    char buf[100] = {0};
    if (fgets(buf, sizeof buf, file_pointer) != NULL)
    {
        current_command = strdup(buf);
    }
}

// Returns the type of the current command.
char *commandTypeParser()
{
    // Check if the current command is an A_COMMAND
    if (current_command[0] == '@')
    {
        return "A_COMMAND";
    }
    // Check if the current command is a C_COMMAND
    else if (strchr(current_command, '=') || strchr(current_command, ';'))
    {
        return "C_COMMAND";
    }
    // Check if the current command is an L_COMMAND
    else if (current_command[0] == '(' && current_command[strlen(current_command) - 3] == ')') // change 3 to 2 for linux
    {
        return "L_COMMAND";
    }
    // If none of the above, return NULL
    else
    {
        return NULL;
    }
}

/*
Returns the symbol or decimal Xxx of the current command @Xxx or (Xxx).
Should be called only when commandType() is A_COMMAND or L_COMMAND.
*/
char *symbolParser()
{
    // Check if the current command is an A_COMMAND
    if (command_type && strcmp(command_type, "A_COMMAND") == 0)
    {
        // Skip the '@' symbol and return the remaining string
        return current_command + 1;
    }
    // Check if the current command is an L_COMMAND
    else if (command_type && strcmp(command_type, "L_COMMAND") == 0)
    {
        // Skip the '(' and ')' symbol from the current command and return the remaining string
        current_command[strlen(current_command) - 3] = '\0';
        return current_command + 1;
    }
    // If none of the above, return NULL
    else
    {
        return NULL;
    }
}

/*
Returns the dest mnemonic in the current C-command (8 possibilities).
Should be called only when commandType() is C_COMMAND.
*/
char *destParser()
{
    // Find the position of the '=' character
    char *equal_sign = strchr(current_command, '=');

    // If '=' is found, extract the destination mnemonic
    if (equal_sign != NULL)
    {
        // Calculate the length of the destination mnemonic
        int length = equal_sign - current_command;

        // Create a new string to store the destination mnemonic
        char *destination = malloc((length + 1) * sizeof(char));

        // Copy the destination mnemonic from the current command
        strncpy(destination, current_command, length);

        // Null-terminate the destination string
        destination[length] = '\0';

        return destination;
    }
    // If '=' is not found, return NULL
    else
    {
        return NULL;
    }
}

/*
Returns the comp mnemonic in the current C-command (28 possibilities).
Should be called only when commandType() is C_COMMAND.
*/
char *compParser()
{
    // Find the position of the '=' character
    char *equal_sign = strchr(current_command, '=');

    // Find the position of the ';' character
    char *semicolon = strchr(current_command, ';');

    // If both '=' and ';' are found, extract the comp mnemonic
    if (equal_sign != NULL && semicolon != NULL)
    {
        // Calculate the length of the comp mnemonic
        int length = semicolon - equal_sign - 1;

        // Create a new string to store the comp mnemonic
        char *comp_mnemonic = malloc((length + 1) * sizeof(char));

        // Copy the comp mnemonic from the current command
        strncpy(comp_mnemonic, equal_sign + 1, length);

        // Null-terminate the comp mnemonic string
        comp_mnemonic[length] = '\0';

        return comp_mnemonic;
    }
    // If only '=' is found, extract the comp mnemonic
    else if (equal_sign != NULL)
    {
        // Calculate the length of the comp mnemonic
        int length = strlen(current_command) - (equal_sign - current_command) - 2;

        // Create a new string to store the comp mnemonic
        char *comp_mnemonic = malloc((length + 1) * sizeof(char));

        // Copy the comp mnemonic from the current command
        strncpy(comp_mnemonic, equal_sign + 1, length);

        // Null-terminate the comp mnemonic string
        comp_mnemonic[length] = '\0';

        return comp_mnemonic;
    }
    // If only ';' is found, extract the comp mnemonic
    else if (semicolon != NULL)
    {
        // Calculate the length of the comp mnemonic
        int length = semicolon - current_command;

        // Create a new string to store the comp mnemonic
        char *comp_mnemonic = malloc((length + 1) * sizeof(char));

        // Copy the comp mnemonic from the current command
        strncpy(comp_mnemonic, current_command, length);

        // Null-terminate the comp mnemonic string
        comp_mnemonic[length] = '\0';

        return comp_mnemonic;
    }
    // If neither '=' nor ';' is found, return NULL
    else
    {
        return NULL;
    }
}

/*
Returns the jump mnemonic in the current C-command (8 possibilities).
Should be called only when commandType() is C_COMMAND.
*/
char *jumpParser()
{
    // Find the position of the ';' character
    char *semicolon = strchr(current_command, ';');

    // If ';' is found, extract the jump mnemonic
    if (semicolon != NULL)
    {
        // Calculate the length of the jump mnemonic
        int length = strlen(current_command) - (semicolon - current_command) - 1;

        // Create a new string to store the jump mnemonic
        char *jump_mnemonic = malloc((length + 1) * sizeof(char));

        // Copy the jump mnemonic from the current command
        strncpy(jump_mnemonic, semicolon + 1, length - 1);

        // Null-terminate the jump mnemonic string
        jump_mnemonic[length] = '\0';

        return jump_mnemonic;
    }
    // If ';' is not found, return NULL
    else
    {
        return NULL;
    }
}
