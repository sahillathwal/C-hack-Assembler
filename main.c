#include "parser.h"
// #include "hashtable.h"
#include "code.h"

int main(int arg, char *vargs[])
{

    // if (arg < 2)
    // {
    //     printf("No input file specified.\n");
    //     return 1;
    // }

    // stores input file arrgumnet to input_file

    input_file = "Add.asm";

    // calling createCodeTables function to create the hash tables
    createCodeTables();

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
            char *dest = destParser();
            printf("Dest code: %s\n", destCode(dest));
        }
        // calling compCode function to get the binary code of the comp
        if (command_type && strcmp(command_type, "C_COMMAND") == 0)
        {
            char *comp = compParser();
            printf("Comp code: %s\n", compCode(comp));
        }
        // calling jumpCode function to get the binary code of the jump
        if (command_type && strcmp(command_type, "C_COMMAND") == 0)
        {
            // printf("Jump code: %s\n", jumpCode(jumpParser()));
        }
    } while (hasMoreCommandsParser() == true);
}