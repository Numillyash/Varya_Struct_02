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
	time_t start_tm;
	// Время окончания тестирования
	time_t end_tm;
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
				return 0; break;
		case moreEqual:
			if (elem->curse_id < conditions[2]->compInt)
				return 0; break;
		case less:
			if (elem->curse_id >= conditions[2]->compInt)
				return 0; break;
		case lessEqual:
			if (elem->curse_id > conditions[2]->compInt)
				return 0; break;
		case equal:
			if (elem->curse_id != conditions[2]->compInt)
				return 0; break;
		case notEqual:
			if (elem->curse_id == conditions[2]->compInt)
				return 0; break;
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
				return 0; break;
		case moreEqual:
			if (elem->lab_id < conditions[3]->compInt)
				return 0; break;
		case less:
			if (elem->lab_id >= conditions[3]->compInt)
				return 0; break;
		case lessEqual:
			if (elem->lab_id > conditions[3]->compInt)
				return 0; break;
		case equal:
			if (elem->lab_id != conditions[3]->compInt)
				return 0; break;
		case notEqual:
			if (elem->lab_id == conditions[3]->compInt)
				return 0; break;
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
				return 0; break;
		case moreEqual:
			if (elem->start_tm < conditions[4]->compTime)
				return 0; break;
		case less:
			if (elem->start_tm >= conditions[4]->compTime)
				return 0; break;
		case lessEqual:
			if (elem->start_tm > conditions[4]->compTime)
				return 0; break;
		case equal:
			if (elem->start_tm != conditions[4]->compTime)
				return 0; break;
		case notEqual:
			if (elem->start_tm == conditions[4]->compTime)
				return 0; break;
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
				return 0; break;
		case moreEqual:
			if (elem->end_tm < conditions[5]->compTime)
				return 0; break;
		case less:
			if (elem->end_tm >= conditions[5]->compTime)
				return 0; break;
		case lessEqual:
			if (elem->end_tm > conditions[5]->compTime)
				return 0; break;
		case equal:
			if (elem->end_tm != conditions[5]->compTime)
				return 0; break;
		case notEqual:
			if (elem->end_tm == conditions[5]->compTime)
				return 0; break;
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
				return 0; break;
		case resultsNotIncludeBoth:
			if (!isResultsNotIncludeBoth(elem, conditions[6]))
				return 0; break;
		case resultsIncludeBoth:
			if (!isResultsIncludeBoth(elem, conditions[6]))
				return 0; break;
		case resultsIncludeAtLeastOne:
			if (!isResultsIncludeAtLeastOne(elem, conditions[6]))
				return 0; break;
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

	char* family = (char*)malloc(sizeof(char) * strlen(lastName));
	strcpy(family, lastName);
	mallocCount++;
	char* name = (char*)malloc(sizeof(char) * strlen(firstName));
	strcpy(name, firstName);
	mallocCount++;

	newElement->first_nm = name;
	newElement->last_nm = family;
	newElement->curse_id = course;
	newElement->lab_id = labID;
	newElement->result = results;
	newElement->start_tm = *startTime;
	newElement->end_tm = *endTime;
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
	printf("%s\t", asctime(gmtime(&(elem->start_tm))));
	printf("%s\tResults\n", asctime(gmtime(&(elem->end_tm))));
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

int deleteNonUniqElements(char whatToDelete[7])
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
			if (!whatToDelete[0] || !strcmp(tmp->last_nm, tmp2->last_nm))
				if (!whatToDelete[1] || !strcmp(tmp->first_nm, tmp2->first_nm))
					if (!whatToDelete[2] || tmp->curse_id == tmp2->curse_id)
						if (!whatToDelete[3] || tmp->lab_id == tmp2->lab_id)
							if (!whatToDelete[4] || tmp->start_tm == tmp2->start_tm)
								if (!whatToDelete[5] || tmp->end_tm == tmp2->end_tm)
									if (!whatToDelete[6] || isResultsSame(tmp, tmp2))
									{
										needToDel[currInd] = 1;
										//printf("%d currind, %d, %d\n", currInd,tmp->lab_id, tmp2->lab_id);
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
	printf("uniq:%d \n", add);
	return add;
}

int deleteFunc(Condition* conditions)
{
	int count = 0;
	DataBaseElement* tmp;
restartCycle:
	tmp = head;
	while (tmp != NULL)
	{
		if (isElementRespondConditions(tmp, conditions))
		{
			goto restartCycle;
			deleteElementFromDB(tmp);
			count++;
		}
		tmp = tmp->nextElement;
	}
	return count;
}

char* formateTime(time_t time)
{
	char* string = asctime(gmtime(&time));
	char* symb = strchr(string, '\n');
	*symb = '\0';
	return string;
}

/// <summary>
/// 
/// </summary>
/// <param name="whatToPrint">Указываются номера как порядок выводимых значений
/// ,-1 для пустых мест (НЕ NULL)
/// </param>
/// <param name="conditions"></param>
int selectFunc(char whatToPrint[7], Condition* conditions[7])
{
	int count = 0;
	DataBaseElement* tmp;
	tmp = head;
	while (tmp != NULL)
	{
		if (isElementRespondConditions(tmp, conditions))
		{
			for (int i = 0; i < 7; i++)
			{
				switch (whatToPrint[i]) {
				case 0:
					printf("last_nm:%s ", tmp->last_nm);
					break;
				case 1:
					printf("first_nm:%s ", tmp->first_nm);
					break;
				case 2:
					printf("curse:%d ", tmp->curse_id);
					break;
				case 3:
					printf("lab_id:%d ", tmp->lab_id);
					break;
				case 4:
					printf("start_tm:%s ", formateTime(tmp->start_tm));
					break;
				case 5:
					printf("end_tm:%s ", formateTime(tmp->end_tm));
					break;
				case 6:
					for (int j = 0; j < 99; j++)
					{
						printf("result:[ ");
						if (tmp->result[j] == 1)
						{
							if(j > 9)
								printf("test%d, ", j+1);
							else
								printf("test0%d, ", j + 1);
						}
						printf("]");
					}					
					break;
				case -1:
					break;
				}
			}

			printf("\n");
			count++;
		}
		tmp = tmp->nextElement;
	}
	return count;
}

int updateFunc(char* lastName, char* firstName, int course, int labID, time_t* startTime, time_t* endTime, int results[99],Condition* conditions[7])
{
	int count = 0;
	DataBaseElement* tmp;
	tmp = head;
	while (tmp != NULL)
	{
		if (isElementRespondConditions(tmp, conditions))
		{
			if (lastName != NULL)
				tmp->last_nm = lastName;
			if (firstName != NULL)
				tmp->first_nm = firstName;
			if (course != -1)
				tmp->curse_id = course;
			if (labID != -1)
				tmp->lab_id = labID;
			if (startTime != NULL)
				tmp->start_tm = startTime;
			if (endTime != NULL)
				tmp->end_tm = endTime;
			if (results != NULL)
				tmp->result = results;
			count++;
		}
		tmp = tmp->nextElement;
	}
	return count;
}