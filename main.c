#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// varabile to store the file arrgument provided by user
char *input_file;

// FILE pointer to store the file pointer created by initializer function
FILE *file_pointer;

int is_ok = EXIT_FAILURE;

// function declerations
int initializer(char *);
bool hasMoreCommands();

int main(int arg, char *vargs[])
{
    // stores input file arrgumnet to input_file
    input_file = vargs[1];

    // calling initializer function to open the file for parsing
    initializer(input_file);

    // checking by printing the content of the input file
    while (hasMoreCommands() == true)
    {
        char buf[100] = {0};
        fgets(buf, sizeof buf, file_pointer);
        printf("%s", buf);
    }
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

// function to check if there are more commands left in the input file
bool hasMoreCommands()
{
    // if the end of the stream has not been reached feof returns zero; hence ture_false gets assgined false
    bool ture_false = (feof(file_pointer) == 0) ? true : false;

    // returns false value if end of file has been reached else returns ture
    return ture_false;
}