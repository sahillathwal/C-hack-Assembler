#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// varabile to store the file arrgument provided by user
extern char *input_file;

// FILE pointer to store the file pointer created by initializer function
extern FILE *file_pointer;

// varaible to store cuurent command
extern char *current_command;

// varaible to store command type
extern char *command_type;

extern int is_ok;

int initializerParser(char *);
bool hasMoreCommandsParser();
void advanceParser();
char *commandTypeParser();
char *symbolParser();
char *destParser();
char *compParser();
char *jumpParser();

#endif /* PARSER_H */
