#include "parser.h"
#include "hashtable.h"

HashTable *ht;
#define TABLE_SIZE 10

char *destCode(char *dest);

int main(int arg, char *vargs[])
{

    // if (arg < 2)
    // {
    //     printf("No input file specified.\n");
    //     return 1;
    // }
    // creates a hash table
    ht = createHashTable();
    // inserts the key value pairs into the hash table
    insert(ht, "null", "000");
    insert(ht, "M", "001");
    insert(ht, "D", "010");
    insert(ht, "MD", "011");
    insert(ht, "A", "100");
    insert(ht, "AM", "101");
    insert(ht, "AD", "110");
    insert(ht, "AMD", "111");

    // stores input file arrgumnet to input_file

    input_file = "Add.asm";
    // calling initializer function to open the file for parsing
    initializerParser(input_file);

    // checking by printing the content of the input file
    do
    {
        // reads the next command from the input and makes it the current command
        advanceParser();

        // if current_commmand is empty line then skip the current iteration
        if (current_command == NULL || current_command[0] == '\r' || current_command[0] == '\n' || current_command[0] == '\0')
        {
            continue;
        }

        printf("\n");

        // prints the current command
        printf("%s", current_command);

        // stores the type of the current command to command_type
        command_type = commandTypeParser();

        // prints the type of the current command
        if (command_type != NULL)
        {
            printf("Command type: %s\n", command_type);
        }
        else
        {
            printf("Invalid command\n");
        }

        // prints the symbol of the current command
        if (command_type && strcmp(command_type, "A_COMMAND") == 0 || command_type && strcmp(command_type, "L_COMMAND") == 0)
        {
            printf("Symbol: %s", symbolParser());
        }

        // prints the destination of the current command
        if (command_type && strcmp(command_type, "C_COMMAND") == 0)
        {
            printf("Destination: %s\n", destParser());
        }

        // prints the comp of the current command
        if (command_type && strcmp(command_type, "C_COMMAND") == 0)
        {
            printf("Comp: %s\n", compParser());
        }
        // prints the jump of the current command
        if (command_type && strcmp(command_type, "C_COMMAND") == 0)
        {
            printf("Jump: %s\n", jumpParser());
        }
        // calling destCode function to get the binary code of the destination
        if (command_type && strcmp(command_type, "C_COMMAND") == 0)
        {
            printf("Destination code: %s\n", destCode(destParser()));
        }
    } while (hasMoreCommandsParser() == true);
}

char *destCode(char *dest)
{
    char *bits = get(ht, dest);
    if (bits == NULL)
    {
        printf("Key not found: %s\n", dest);
        return NULL;
    }
    return strdup(bits);
}