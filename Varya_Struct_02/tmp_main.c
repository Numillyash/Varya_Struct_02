#include "parcer.h"

int main(int argc, char **argv)
{
    FILE *IFile = NULL;
    char ILine[MAX_STRING_SIZE + 1];
    int16_t len = 0;
    int32_t read;

    char WRead[MAX_STRING_SIZE];

    if (argc > 1)
    {
        if (argc == 3)
        {
            // argc OK!
            IFile = fopen(argv[2], "r");
            if (IFile == NULL)
            {
                printf("Wrong File!\n");
                exit(WRONG_ARGUMENT_FAILURE);
            }
        }

        else
        {
            printf("Wrong Arguments!\nUsage ./Lab.exe -f <file.txt>\n");
            exit(WRONG_ARGUMENT_FAILURE);
        }
        
        while ((read = fgets(&ILine, MAX_STRING_SIZE, IFile)) != NULL)
        {
            printf("%s", ILine);
            parceLine(ILine);
        }
        printDataBase();

        fclose(IFile);

        exit(EXIT_SUCCESS); // Comment if you want continious reading after parsing file
    } // if (argc > 1) -- correct

    int iExit = 0;
    printf("Enter your request.\nType \"stop\" to stop reading\n\n");
    while(!iExit)
    {
        printf("> ");
        gets(WRead);
        if (!strcmp("stop", WRead))
        {
            break;
        }

        parceLine(WRead);
    }

    printDataBase();
    exit(EXIT_SUCCESS);
}