#include "parser.h"
// #include "hashtable.h"
#include "code.h"
#include "symbol.h"
#include <ctype.h>

bool isNumber(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

char *decimalToBinary(int n, int bits)
{
    static char binaryNumber[17];
    for (int i = 0; i < bits; i++)
    {
        binaryNumber[bits - 1 - i] = (n & 1) + '0';
        n >>= 1;
    }
    binaryNumber[bits] = '\0'; // Add the null character at the end
    return binaryNumber;
}

int main(int arg, char *vargs[])
{
    // variable to store the input file name
    char *input_file;

    // if the number of arguments is less than 2 then print the error message
    if (arg < 2)
    {
        printf("Usage: ./assembler <input_file>\n");
        return 1;
    }

    // if the number of arguments is 2 then assign the input file name to input_file
    if (arg == 2)
    {
        input_file = vargs[1];
    }

    // calling createCodeTables function to create the hash tables
    createCodeTables();

    // calling initializer function to open the file for parsing
    initializerParser(input_file);

    // calling constructor function to initialize the symbol table
    constructor();

    // calling initSymbolTable function to initialize the symbol table
    initSymbolTable();

    // variable to record the ROM address into which the current command will be eventually loaded
    int address = 0;

    // variable to record RAM address into which the next variable will be loaded
    int ram_address = 16;

    // opens an output file named based on inputfile name with extension .hack and prepares to write to it
    char output_file_name[100];
    strcpy(output_file_name, input_file);
    char *dot = strrchr(output_file_name, '.');
    if (dot != NULL)
    {
        *dot = '\0'; // remove the extension
    }
    strcat(output_file_name, ".hack");
    FILE *output_file = fopen(output_file_name, "w");
    if (output_file == NULL)
    {
        printf("Error opening output file.\n");
        return 1;
    }

    // First Pass
    do
    {
        // reads the next command from the input and makes it the current command
        advanceParser();

        // if current_commmand is empty line then skip the current iteration
        if (current_command == NULL || current_command[0] == '\r' || current_command[0] == '\n' || current_command[0] == '\0')
        {
            continue;
        }

        // stores the type of the current command to command_type
        command_type = commandTypeParser();

        if (command_type != NULL)
        {
            // adress incremented by 1 if a C-instruction or an A-instruction is encountered
            if (strcmp(command_type, "C_COMMAND") == 0 || strcmp(command_type, "A_COMMAND") == 0)
            {
                address++;
            }
            /*
            Each time a pseudocommand (Xxx)is encountered, add a new entry to the symbol table, associating Xxx with the ROM
            address that will eventually store the next command in the program
            */
            if (strcmp(command_type, "L_COMMAND") == 0)
            {
                addEntry(symbolParser(), address);
            }
        }

    } while (hasMoreCommandsParser() == true);

    initializerParser(input_file);
    // second pass
    do
    {

        // reads the next command from the input and makes it the current command
        advanceParser();

        // if current_commmand is empty line then skip the current iteration
        if (current_command == NULL || current_command[0] == '\r' || current_command[0] == '\n' || current_command[0] == '\0')
        {
            continue;
        }

        // stores the type of the current command to command_type
        command_type = commandTypeParser();

        // prints the type of the current command
        if (command_type != NULL)
        {
            /*
            Each time a symbolic A-instruction is encountered, namely, @Xxx where Xxx is a symboland not a number, look up Xxx in the symbol table. If the symbol is found in the
            table, replace it with its numeric meaning and complete the command’s translation.If the symbol is not found in the table, then it must represent a new variable. To
            handle it, add the pair (Xxx, n) to the symbol table, where n is the next availableRAM address
            */
            if (strcmp(command_type, "A_COMMAND") == 0)
            {
                char *symbol = symbolParser();
                if (isNumber(symbol) == false)
                {
                    if (contains(symbol) == false)
                    {
                        addEntry(symbol, ram_address);
                        ram_address++;
                    }
                }
            }
        }
    } while (hasMoreCommandsParser() == true);

    initializerParser(input_file);
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
        printf("%s\n", current_command);

        // stores the type of the current command to command_type
        command_type = commandTypeParser();

        if (command_type != NULL)
        {
            // prints the type of the current command
            printf("Command type: %s\n", command_type);
        }
        else
        {
            printf("Invalid command\n");
        }

        // // prints the symbol of the current command
        // if (command_type && strcmp(command_type, "A_COMMAND") == 0 || command_type && strcmp(command_type, "L_COMMAND") == 0)
        // {
        //     printf("Symbol: %s\n", symbolParser());
        // }

        // // prints the destination of the current command
        // if (command_type && strcmp(command_type, "C_COMMAND") == 0)
        // {
        //     printf("Destination: %s\n", destParser());
        // }

        // // prints the comp of the current command
        // if (command_type && strcmp(command_type, "C_COMMAND") == 0)
        // {
        //     printf("Comp: %s\n", compParser());
        // }
        // // prints the jump of the current command
        // if (command_type && strcmp(command_type, "C_COMMAND") == 0)
        // {
        //     printf("Jump: %s\n", jumpParser());
        // }
        // // calling destCode function to get the binary code of the destination
        // if (command_type && strcmp(command_type, "C_COMMAND") == 0)
        // {
        //     char *dest = destParser();
        //     printf("Dest code: %s\n", destCode(dest));
        // }
        // // calling compCode function to get the binary code of the comp
        // if (command_type && strcmp(command_type, "C_COMMAND") == 0)
        // {
        //     char *comp = compParser();
        //     printf("Comp code: %s\n", compCode(comp));
        // }
        // // calling jumpCode function to get the binary code of the jump
        // if (command_type && strcmp(command_type, "C_COMMAND") == 0)
        // {
        //     char *jump = jumpParser();
        //     printf("Jump code: %s\n", jumpCode(jump));
        // }

        /*
        For each C-instruction, the program concatenates the translated binary codes of the
        instruction fields into a single 16-bit word. Next, the program writes this word into
        the Prog.hack file. For each A-instruction of type @Xxx, the program translates the
        decimal constant returned by the parser into its binary representation and writes the
        resulting 16-bit word into the Prog.hack file.
        */
        if (command_type && strcmp(command_type, "C_COMMAND") == 0)
        {
            char *dest = destParser();
            char *comp = compParser();
            char *jump = jumpParser();
            char *dest_code = destCode(dest);
            char *comp_code = compCode(comp);
            char *jump_code = jumpCode(jump);

            char c_instruction_code[17]; // 16 bits plus null terminator
            strcpy(c_instruction_code, "111");
            strcat(c_instruction_code, comp_code);
            strcat(c_instruction_code, dest_code);
            strcat(c_instruction_code, jump_code);

            printf("\nC instruction code: %s\n", c_instruction_code);
            fprintf(output_file, "%s\n", c_instruction_code);
        }
        if (command_type && strcmp(command_type, "A_COMMAND") == 0)
        {
            char *symbol = symbolParser();
            if (isNumber(symbol) == true)
            {
                char a_instruction_code[17]; // 16 bits plus null terminator
                strcpy(a_instruction_code, "0");
                strcat(a_instruction_code, decimalToBinary(atoi(symbol), 15));

                printf("\nA instruction code: %s\n", a_instruction_code);
                fprintf(output_file, "%s\n", a_instruction_code);
            }
            else
            {
                char a_instruction_code[17]; // 16 bits plus null terminator
                strcpy(a_instruction_code, "0");
                strcat(a_instruction_code, decimalToBinary(getAddress(symbol), 15));

                printf("\nA instruction code: %s\n", a_instruction_code);
                fprintf(output_file, "%s\n", a_instruction_code);
            }
        }
    } while (hasMoreCommandsParser() == true);

    // print ht_symbol table
    printSortedHashTable(ht_symbol);

    // free the memory allocated for the ht_symbol table
    freeHashTable(ht_symbol);
}