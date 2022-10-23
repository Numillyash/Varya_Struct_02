#include "parcer.h"

#ifdef _WIN32
size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}
#endif

int main(int argc, char** argv)
{
    FILE* IFile = NULL;
    char* ILine = NULL;
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

        while ((read = getline(&ILine, &len, IFile)) != -1) {
            // printf("Retrieved line of length %zu:\n", read);
            printf("%s", ILine);
            parceLine(ILine);
        }
        printDataBase();

        fclose(IFile);
        if (ILine)
            free(ILine);
        exit(EXIT_SUCCESS);
    } // if (argc > 1) -- correct
}