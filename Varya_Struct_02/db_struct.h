#pragma once

#include "malloc_count.h"

typedef struct _dbElement
{
	// Фамилия
	char* last_nm;
	// Имя
	char* first_nm;
	// Курс
	int curse_id;
	// ID лабораторной
	int lab_id;
	// Время начала тестирования
	time_t* start_tm;
	// Время окончания тестирования
	time_t* end_tm;
	// Множество: пройденные тесты (99)
	int* result;
	// Следующий элемент списка
	struct _dbElement* nextElement;
}DataBaseElement;

DataBaseElement* head;
uint64_t dataBaseSize = 0;

int putElementToDB(char* lastName, char* firstName, int course, int labID, time_t* startTime, time_t* endTime, int results[99])
{
	DataBaseElement* newElement = (DataBaseElement*)malloc(sizeof(DataBaseElement));
	if (newElement == NULL)
		return ALLOC_FAILURE;
	mallocCount++;
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
	return SUCCESS;
}

void deleteElementFromDB(DataBaseElement* elem)
{
	if (elem == head)
	{
		DataBaseElement* tmp = head;
		head = head->nextElement;
		free(tmp);
		freeCount++;
	}
	else
	{
		DataBaseElement* tmp = head;
		while (tmp != NULL && tmp->nextElement != elem)
			tmp = tmp->nextElement;
		DataBaseElement* tmp2 = tmp->nextElement;
		tmp->nextElement = tmp2->nextElement;
		free(tmp2);
		freeCount++;
	}
}

void printElement(DataBaseElement* elem)
{
	printf("Element:\n\tName: %s %s\n\tCourse: %d, lab N%d\n\t",
		elem->first_nm, elem->last_nm, elem->curse_id, elem->lab_id);
	printf("%s\t", asctime(gmtime(elem->start_tm)));
	printf("%s\tResults\n", asctime(gmtime(elem->end_tm)));
	/*for (int i = 0; i < 99; i++)
	{
		printf("%d ", elem->result[i]);
	}*/
	printf("\n");
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

int isResultsSame(DataBaseElement* e1, DataBaseElement* e2)
{
	for (int i = 0; i < 99; i++)
	{
		if (e1->result[i] != e2->result[i])
			return 0;
	}
	return 1;
}

int deleteNonUniqElements()
{
	char* needToDel = (char*)malloc(sizeof(char)*dataBaseSize);
	mallocCount++;

	// Цикл проверок
	DataBaseElement* tmp = head;
	DataBaseElement* tmp2 = head;
	int currInd = 0;
	while (tmp != NULL)
	{
		tmp2 = tmp->nextElement;
		while (tmp2 != NULL)
		{
			if (!strcmp(tmp->last_nm, tmp2->last_nm))
				if (!strcmp(tmp->first_nm, tmp2->first_nm))
					if (tmp->curse_id == tmp2->curse_id)
						if (tmp->lab_id == tmp2->lab_id)
							if (tmp->start_tm == tmp2->start_tm)
								if (tmp->end_tm == tmp2->end_tm)
									if (isResultsSame(tmp, tmp2))
									{
										needToDel[currInd] = 1;
									}
			// Добавить сравнение по тестам
			tmp2 = tmp2->nextElement;
		}
		tmp = tmp->nextElement;
		currInd++;
	}

	//for (uint64_t i = 0; i < dataBaseSize; i++)
	//		printf("%d ", needToDel[i]);

	//for (uint64_t i = 0; i < dataBaseSize; i++)
	//	if(needToDel[i] == 1)
	//		printf("\nDB elemeny number %d is need to delete", i+1);

	int add = 0;
	currInd = 0;
	tmp = head;
	while (tmp == head && needToDel[add+currInd] == 1)
	{
		deleteElementFromDB(head);
		tmp = head;
		add++;
	}
	while (tmp != NULL && tmp->nextElement!= NULL)
	{
		if (needToDel[add + currInd + 1] == 1)
		{
			deleteElementFromDB(tmp->nextElement);
			add++;
		}
		else
		{
			tmp = tmp->nextElement;
			currInd++;
		}

	}
}

//struct condition
//{
//	field;
//	enum
//	int
//	char**
//};