#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNLEN 256
#define MAXARGS 10

#define FAIL -1
#define GETSTRING_ERR_RE -1
#define GETSTRING_ERR_OVERFLOW -2

#ifndef _WIN32
    #define gets_s gets
    #define strcpy_s strcpy
#endif

int getString(char* str, const int size)
{
	char* buf = (char*) malloc(size + 1);
	if (gets_s(buf) == NULL)
	{
		return GETSTRING_ERR_RE;
	}

	if (strlen(buf) == size)
	{
		return GETSTRING_ERR_OVERFLOW;
	}

	// strcpy_s(str, size, buf);
    strcpy(str, buf);
	free(buf);
	
	return 0;
}

int checkCommand()
{

}

int parseCommand(char* str)
{
	int result;
    char* call = NULL; // command + args

	char* command = (char*) malloc(UNLEN + 1);
	
	char** args = (char**) calloc(MAXARGS, UNLEN + 1);
	int nArgs = -1; // number of args
    
	result = getString(call, UNLEN); // get call

	if (result != 0)
	{
		printf("ERROR on 40: %d", result);
		return FAIL;
	}

	// create a temporary string for strtok ()
    char* tmp = (char *)malloc(UNLEN + 1);
    strcpy(tmp, call);
    
	char* pch = strtok(tmp, " ,"); // separate by "," and " "

	int nTokens = 0; // number of parsed tokens
	while (pch != NULL)
	{
		if (!nTokens) // nTokens == 0
		{
			strcpy(command, pch);
			
		}

		pch = strtok(NULL, " ,");
		nTokens++;
	}
	
    return 0;

	cleanup:
	if (call != NULL)
		free(call);

	if (command != NULL)
		free(command);

	if (args != NULL)
		free(args);
}