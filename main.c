#include <stdio.h>

// input file to store the file arrgument provided by user
char *input_file;

// FILE pointer to store the file pointer created by initializer function
FILE *file_pointer;

// function declerations
void initializer(char *);

int main(int arg, char *vargs[])
{
    // stores input file arrgumnet to input_file
    input_file = vargs[1];

    // calling initializer function to open the file for parsing
    initializer(input_file);
}

// Opens the input file/stream for parsing and stores the file pointer to file_pointer.
void initializer(char *input_file)
{
    file_pointer = fopen(input_file, "r");
}