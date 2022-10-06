#pragma once

#include "malloc_count.h"

enum cond
{
	more,
	moreEqual,
	less,
	lessEqual,
	equal,
	notEqual,
	resultsAreOnly,
	resultsNotIncludeBoth,
	resultsIncludeBoth,
	resultsIncludeAtLeastOne,
	stringIsOneOf
};

typedef struct _condition
{
	enum cond condition;
	int compInt;
	time_t compTime;
	char** compString;
	int compStringCount;
	int* compResults;
}Condition;

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

int isResultsSame(DataBaseElement* e1, DataBaseElement* e2)
{
	for (int i = 0; i < 99; i++)
	{
		if (e1->result[i] != e2->result[i])
			return 0;
	}
	return 1;
}

int isResultsOneOnly(DataBaseElement* elem, Condition* condition)
{
	for (int i = 0; i < 99; i++)
	{
		if (elem->result[i] != condition->compResults[i])
			return 0;
	}
	return 1;
}

int isResultsIncludeBoth(DataBaseElement* elem, Condition* condition)
{
	for (int i = 0; i < 99; i++)
	{
		if (elem->result[i] != condition->compResults[i] && condition->compResults[i])
			return 0;
	}
	return 1;
}

int isResultsIncludeAtLeastOne(DataBaseElement* elem, Condition* condition)
{
	for (int i = 0; i < 99; i++)
	{
		if (elem->result[i] == condition->compResults[i] && condition->compResults[i])
			return 1;
	}
	return 0;
}

int isResultsNotIncludeBoth(DataBaseElement* elem, Condition* condition)
{
	for (int i = 0; i < 99; i++)
	{
		if (elem->result[i] == condition->compResults[i] && condition->compResults[i])
			return 0;
	}
	return 1;
}

int isStringOneOf(char* string, Condition* condition)
{
	for (int i = 0; i < condition->compStringCount; i++)
		if (!strcmp(string, condition->compString))
			return 1;
	return 0;
}

int isElementRespondConditions(DataBaseElement* elem, Condition* conditions[7])
{
	// Проверка на фамилию
	if (conditions[0] != NULL)
	{
		if (conditions[0]->condition == stringIsOneOf)
			if (!isStringOneOf(elem->last_nm, conditions[0]))
				return 0;
	}
	// Проверка на имя
	if (conditions[1] != NULL)
	{
		if (conditions[0]->condition == stringIsOneOf)
			if (!isStringOneOf(elem->first_nm, conditions[0]))
				return 0;
	}
	// Проверка на курс
	if (conditions[2] != NULL)
	{
		switch (conditions[2]->condition)
		{
		case more:
			if (elem->curse_id <= conditions[2]->compInt)
				return 0;
		case moreEqual:
			if (elem->curse_id < conditions[2]->compInt)
				return 0;
		case less:
			if (elem->curse_id >= conditions[2]->compInt)
				return 0;
		case lessEqual:
			if (elem->curse_id > conditions[2]->compInt)
				return 0;
		case equal:
			if (elem->curse_id != conditions[2]->compInt)
				return 0;
		case notEqual:
			if (elem->curse_id == conditions[2]->compInt)
				return 0;
		default:
			break;
		}
	}
	// Проверка на ID лабораторной
	if (conditions[3] != NULL)
	{
		switch (conditions[3]->condition)
		{
		case more:
			if (elem->lab_id <= conditions[3]->compInt)
				return 0;
		case moreEqual:
			if (elem->lab_id < conditions[3]->compInt)
				return 0;
		case less:
			if (elem->lab_id >= conditions[3]->compInt)
				return 0;
		case lessEqual:
			if (elem->lab_id > conditions[3]->compInt)
				return 0;
		case equal:
			if (elem->lab_id != conditions[3]->compInt)
				return 0;
		case notEqual:
			if (elem->lab_id == conditions[3]->compInt)
				return 0;
		default:
			break;
		}
	}
	// Проверка на время начала теста
	if (conditions[4] != NULL)
	{
		switch (conditions[4]->condition)
		{
		case more:
			if (elem->start_tm <= conditions[4]->compTime)
				return 0;
		case moreEqual:
			if (elem->start_tm < conditions[4]->compTime)
				return 0;
		case less:
			if (elem->start_tm >= conditions[4]->compTime)
				return 0;
		case lessEqual:
			if (elem->start_tm > conditions[4]->compTime)
				return 0;
		case equal:
			if (elem->start_tm != conditions[4]->compTime)
				return 0;
		case notEqual:
			if (elem->start_tm == conditions[4]->compTime)
				return 0;
		default:
			break;
		}
	}
	// Проверка на время конца теста
	if (conditions[5] != NULL)
	{
		switch (conditions[5]->condition)
		{
		case more:
			if (elem->end_tm <= conditions[5]->compTime)
				return 0;
		case moreEqual:
			if (elem->end_tm < conditions[5]->compTime)
				return 0;
		case less:
			if (elem->end_tm >= conditions[5]->compTime)
				return 0;
		case lessEqual:
			if (elem->end_tm > conditions[5]->compTime)
				return 0;
		case equal:
			if (elem->end_tm != conditions[5]->compTime)
				return 0;
		case notEqual:
			if (elem->end_tm == conditions[5]->compTime)
				return 0;
		default:
			break;
		}
	}
	// Проверка на результаты
	if (conditions[6] != NULL)
	{
		switch (conditions[6]->condition)
		{
		case resultsAreOnly:
			if (!isResultsOneOnly(elem, conditions[6]))
				return 0;
		case resultsNotIncludeBoth:
			if (!isResultsNotIncludeBoth(elem, conditions[6]))
				return 0;
		case resultsIncludeBoth:
			if (!isResultsIncludeBoth(elem, conditions[6]))
				return 0;
		case resultsIncludeAtLeastOne:
			if (!isResultsIncludeAtLeastOne(elem, conditions[6]))
				return 0;
		}
	}
	return 1;
}

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

int deleteNonUniqElements()
{
	char* needToDel = (char*)malloc(sizeof(char) * dataBaseSize);
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
	while (tmp == head && needToDel[add + currInd] == 1)
	{
		deleteElementFromDB(head);
		tmp = head;
		add++;
	}
	while (tmp != NULL && tmp->nextElement != NULL)
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
	return add;
}

//struct condition
//{
//	field;
//	enum
//	int
//	char**
//};