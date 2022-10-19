#pragma once
#include "db_struct.h"

int f_proverka(const char* y)
{
	const char* com[6] = { "insert", "select", "delete", "update", "uniq", "exit" };
	for (int i = 0; i < 6; i++)
	{
		if (strcmp(y, com[i]) == 0)
			return i + 1;
	}
	return -1;
}

int getWordsAndCount(char* line, char** array)
{
	char buf[500];
	strcpy(buf, line);
	char* pch = strtok(buf, " ,");
	int count = 0;

	while (pch != NULL)                         // пока есть лексемы
	{
		pch = strtok(NULL, " ,");
		count++;
	}

	array = (char**)malloc(sizeof(char*) * count);
	mallocCount++;

	strcpy(buf, line);
	pch = strtok(buf, " ,");
	count = 0;

	while (pch != NULL)                         // пока есть лексемы
	{
		array[count] = (char*) malloc(sizeof(char)*50);
		mallocCount++;
		strcpy(array[count], pch);
		pch = strtok(NULL, " ,");
		count++;
	}

	for (int i = 0; i < count; i++)
	{
		printf("Word is: %s\n", array[i]);
	}
}

void parceLine(char* input)
{
	int x = f_proverka(input);
	switch (x)
	{

	case 6:
		while (head != NULL)
		{
			deleteElementFromDB(head);
		}
		break;
	default:
		exit(100);
	}
}