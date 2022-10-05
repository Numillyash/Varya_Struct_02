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
	// Множество: пройденные тесты
	char** result;
	// Размер множества пройденных тестов
	int result_count;
	// Следующий элемент списка
	struct _dbElement* nextElement;
}DataBaseElement;

DataBaseElement* head;
uint64_t dataBaseSize = 0;

int putElementToDB(char* lastName, char* firstName, int course, int labID, time_t* startTime, time_t* endTime, char** results, int resultCount)
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

int deleteElementsWithParametres(char* lastName, char* firstName, int course, int labID, time_t* startTime, time_t* endTime, char** results, int resultCount)
{
	DataBaseElement* etalon = (DataBaseElement*)malloc(sizeof(DataBaseElement));
	if (etalon == NULL)
		return ALLOC_FAILURE;
	mallocCount++;
	etalon->first_nm = firstName;
	etalon->last_nm = lastName;
	etalon->curse_id = course;
	etalon->lab_id = labID;
	etalon->result = results;
	etalon->start_tm = startTime;
	etalon->end_tm = endTime;
	etalon->result_count = resultCount;
	etalon->nextElement = NULL;

	int lastElement = -1;

	// Цикл проверок
	DataBaseElement* tmp = head;
	int currInd = 0;
	while (tmp != NULL)
	{
		if (etalon->last_nm == NULL || !strcmp(etalon->last_nm, tmp->last_nm))
			if (etalon->first_nm == NULL || !strcmp(etalon->first_nm, tmp->first_nm))
				if (etalon->curse_id == NULL || etalon->curse_id == tmp->curse_id)
					if (etalon->lab_id == NULL || etalon->lab_id == tmp->lab_id)
						if (etalon->start_tm == NULL || etalon->start_tm == tmp->start_tm)
							if (etalon->end_tm == NULL || etalon->end_tm == tmp->end_tm)
							{
								lastElement = currInd;
							}
		// Добавить сравнение по тестам
		tmp = tmp->nextElement;
		currInd++;
	}

	currInd = 0;

	tmp = head;
	while (tmp != NULL)
	{
		if (etalon->last_nm == NULL || !strcmp(etalon->last_nm, tmp->last_nm))
			if (etalon->first_nm == NULL || !strcmp(etalon->first_nm, tmp->first_nm))
				if (etalon->curse_id == NULL || etalon->curse_id == tmp->curse_id)
					if (etalon->lab_id == NULL || etalon->lab_id == tmp->lab_id)
						if (etalon->start_tm == NULL || etalon->start_tm == tmp->start_tm)
							if (etalon->end_tm == NULL || etalon->end_tm == tmp->end_tm)
								if (currInd != lastElement)
								{
									DataBaseElement* tmp2 = tmp;
									tmp = tmp->nextElement;
									deleteElementFromDB(tmp2);
									lastElement--;
									continue;
								}

		// Добавить сравнение по тестам
		tmp = tmp->nextElement;
		currInd++;
	}

}