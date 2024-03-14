#include <stdio.h>
#include <stdlib.h>

// input file to store the file arrgument provided by user
char *input_file;

// FILE pointer to store the file pointer created by initializer function
FILE *file_pointer;

int is_ok = EXIT_FAILURE;
// function declerations
int initializer(char *);

int main(int arg, char *vargs[])
{
    // stores input file arrgumnet to input_file
    input_file = vargs[1];

    // calling initializer function to open the file for parsing
    initializer(input_file);
    int c;                                   // note: int, not char, required to handle EOF
    while ((c = fgetc(file_pointer)) != EOF) // standard C I/O file reading loop
        putchar(c);
}

// Opens the input file/stream for parsing and stores the file pointer to file_pointer.
int initializer(char *input_file)
{
    file_pointer = fopen(input_file, "r");
    // check if file opening failed
    if (!file_pointer)
    {
        perror("File opening failed");
        return is_ok;
    }
}