#pragma once

#include "config.h"

typedef struct _dbElement
{
	char* last_nm;
	char* first_nm;
	int curse_id;
	int lab_id;
	time_t* start_tm;
	time_t* end_tm;
	char** result;
	int result_count;
	struct _dbElement* nextElement;
}DataBaseElement;

DataBaseElement* head;
uint64_t dataBaseSize = 0;

int putElementToDB(char* lastName, char* firstName, int course, int labID, time_t *startTime, time_t *endTime, char** results, int resultCount)
{
	DataBaseElement* newElement = (DataBaseElement*)malloc(sizeof(DataBaseElement));
	newElement->first_nm = firstName;
	newElement->last_nm = lastName;
	newElement->curse_id = course;
	newElement->lab_id = labID;
	newElement->result = results;
	newElement->start_tm = startTime;
	newElement->end_tm = endTime;
	newElement->result_count = resultCount;
	newElement->nextElement = NULL;

	if (head != NULL)
	{
		DataBaseElement* tmp = head;
		while (tmp->nextElement != NULL)
		{
			tmp = tmp->nextElement;
		}
		tmp->nextElement = newElement;
	}
	else
	{
		head = newElement;
	}

	dataBaseSize++;
}

void printElement(DataBaseElement* elem)
{
	printf("Element:\n\tFirst name: %s\n\tLast name: %s\n\tCourse: %d\n\tLab number: %d\n\t", 
		elem->first_nm, elem->last_nm, elem->curse_id, elem->lab_id);
	printf("%s\t", asctime(gmtime(elem->start_tm)));
	printf("%s\tResults\n", asctime(gmtime(elem->end_tm)));
	for (int i = 0; i < elem->result_count; i++)
	{
		printf("\t\t%s\n", elem->result[i]);
	}
}

void printDataBase()
{
	DataBaseElement* tmp = head;
	while (tmp != NULL)
	{
		printElement(tmp);
		tmp = tmp->nextElement;
	}
}