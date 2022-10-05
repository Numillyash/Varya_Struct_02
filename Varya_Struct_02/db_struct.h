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
	struct _dbElement* nextElement;
}DataBaseElement;

DataBaseElement* head;
uint64_t dataBaseSize = 0;

int putElementToDB(char* lastName, char* firstName, int course, int labID, time_t *startTime, time_t *endTime, char** results)
{
	DataBaseElement* newElement = (DataBaseElement*)malloc(sizeof(DataBaseElement));
	newElement->first_nm = firstName;
	newElement->last_nm = lastName;
	newElement->curse_id = course;
	newElement->lab_id = labID;
	newElement->result = results;
	newElement->start_tm = startTime;
	newElement->end_tm = endTime;
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