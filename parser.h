#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// varabile to store the file arrgument provided by user
char *input_file;

// FILE pointer to store the file pointer created by initializer function
FILE *file_pointer;

// varaible to store cuurent command
char *current_command;

// varaible to store command type
char *command_type;

int is_ok = EXIT_FAILURE;

int initializerParser(char *);
bool hasMoreCommandsParser();
void advanceParser();
char *commandTypeParser();
char *symbolParser();
char *destParser();
char *compParser();
char *jumpParser();

#endif /* PARSER_H */
