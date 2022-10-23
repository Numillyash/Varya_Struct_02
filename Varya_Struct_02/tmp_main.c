#include "parcer.h"

int main(int argc, char **argv)
{
    FILE *IFile = NULL;
    char *ILine = NULL;
    size_t len = 0;
    ssize_t read;

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

        while ((read = getline(&ILine, &len, IFile)) != -1)
        {
            // printf("Retrieved line of length %zu:\n", read);
            printf("%s", ILine);
            parceLine(ILine);
        }

        fclose(IFile);
        if (ILine)
            free(ILine);
        exit(EXIT_SUCCESS);
    } // if (argc > 1) -- correct
}