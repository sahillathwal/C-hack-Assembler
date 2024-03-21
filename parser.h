#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

int initializerParser(char *);
bool hasMoreCommandsParser();
void advanceParser();
char *commandTypeParser();
char *symbolParser();
char *destParser();
char *compParser();
char *jumpParser();

#endif /* PARSER_H */
