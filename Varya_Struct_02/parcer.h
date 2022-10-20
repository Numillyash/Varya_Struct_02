#pragma once
#include "db_struct.h"

int workMode(char* y)
{
	const char* com[6] = { "insert", "select", "delete", "update", "uniq", "exit" };
	for (int i = 0; i < 6; i++)
	{
		if (strcmp(y, com[i]) == 0)
			return i + 1;
	}
	return -1;
}

void parceCondition();

int isField(char* str)
{
	// 0 -> 6 fields
	if (!strcmp("last_nm", str))
		return 0;
	if (!strcmp("first_nm", str))
		return 1;
	if (!strcmp("curse_id", str))
		return 2;
	if (!strcmp("lab_id", str))
		return 3;
	if (!strcmp("start_tm", str))
		return 4;
	if (!strcmp("end_tm", str))
		return 5;
	if (!strcmp("result", str))
		return 6;
	return -1;
}

// ���������� ����� ����, ���� ��� ���������� � �������
int isChangingField(char* line)
{
	char* eq = strchr(line, '=');
	if (eq != NULL && *(eq + 1) != '=')
	{
		char buf[500], ** array;
		strcpy(buf, line);
		char* pch = strtok(buf, "=");
		int x = isField(pch);
		return x;
	}
	else
		return -1;
}

int parceField(char* line, int* _field_num, char** _string, int* _int, time_t** _time, int* results)
{
	int field_num = isChangingField(line);
	int i;
	if (field_num != -1)
	{
		char* st1 = strtok(line, "=");
		char* st2 = strtok(NULL, "=");
		switch (field_num)
		{
		case 0:
		case 1:
			(*_string) = st2;
			*_field_num = field_num;
			return 1;
		case 2:
		case 3:
			i = atoi(st2);
			*_int = i;
			*_field_num = field_num;
			return 1;
		case 4:
		case 5:
			*_field_num = field_num;
			time_t result = 0;
			int year = 0, month = 0, day = 0, hour = 0, min = 0, sec = 0;
			if (sscanf(st2, "%4d.%2d.%2d!%2d:%2d:%2d", &year, &month, &day, &hour, &min, &sec) == 6) {
				struct tm breakdown = { 0 };
				breakdown.tm_year = year - 1900; /* years since 1900 */
				breakdown.tm_mon = month - 1;
				breakdown.tm_mday = day;
				breakdown.tm_hour = hour+3;
				breakdown.tm_min = min;
				breakdown.tm_sec = sec;

				if ((result = mktime(&breakdown)) == (time_t)-1) {
					return -1;
				}

				//puts(ctime(&result));
				//printf("%s %d\n", formateTime(&result), result);
				(*_time) = &result;
				return 1;
			}
			else {
				return -1;
			}
			return 1;
		case 6:
			*_field_num = field_num;
			results[0] = 0;
			break;
		default:
			break;
		}
	}
	else
		return -1;
}

int getWordsAndCount(char* line, char*** arr)
{
	char buf[500], ** array;
	strcpy(buf, line);
	char* pch = strtok(buf, " ,");
	int count = 0;

	while (pch != NULL)                         // ���� ���� �������
	{
		pch = strtok(NULL, " ,");
		count++;
	}

	if (count == 0)return 0;

	array = (char**)malloc(sizeof(char*) * count);
	mallocCount++;

	strcpy(buf, line);
	pch = strtok(buf, " ,");
	count = 0;

	while (pch != NULL)                         // ���� ���� �������
	{
		array[count] = (char*)malloc(sizeof(char) * 50);
		mallocCount++;
		strcpy(array[count], pch);
		pch = strtok(NULL, " ,");
		count++;
	}

	/*for (int i = 0; i < count; i++)
	{
		printf("Word is: %s\n", array[i]);
	}*/
	*arr = array;
	return count;
}

void error(char* input)
{
	char* buf[21];
	strncpy(buf, input, 20);

	printf("\nnot correct");
	printf("%s\n", buf);
}

void parceLine(char* input)
{
	char** wrd = NULL;

	int lixCount = getWordsAndCount(input, &wrd);
	char whatToSearch[7] = { 0,0,0,0,0,0,0 };
	char family[50], name[50], * str = NULL;
	int ints[2] = { 0,0 };
	int f_num = -1;
	int _int = -1;
	time_t* tim = NULL, start = 0, end=0;
	int stroks[99];

	if (lixCount != 0) {
		int x = workMode(wrd[0]);
		switch (x)
		{
		case 1: //insert
			if (lixCount != 8) {
				error(input); exit(100);
			}
			
			for (int i = 1; i < lixCount; i++)
			{

				x = parceField(wrd[i], &f_num, &str, &_int, &tim, stroks);
				if (x == -1)
				{
					error(input); exit(100);
				}
				else
				{
					whatToSearch[f_num]++;
					switch (f_num)
					{
					case 0:
						strcpy(family, str);
						break;
					case 1:
						strcpy(name, str);
						break;
					case 2:
						ints[0] = _int;
						break;
					case 3:
						ints[1] = _int;
						break;
					case 4:
						start = *tim;
						break;
					case 5:
						end = *tim;
						break;
					case 6:
						break;
					default:
						error(input); exit(100);
						break;
					}
				}
			}
			for (int i = 0; i < 7; i++)
			{
				if (whatToSearch[i] >= 2)
				{
					error(input); exit(100);
				}
			}
			putElementToDB(family, name, ints[0], ints[1], &start, &end, stroks);
			break;
		case 5: //uniq
			if (lixCount > 7) {
				error(input); exit(100);
			}
			for (int i = 1; i < lixCount; i++)
			{
				x = isField(wrd[i]);
				if (x == -1)
				{
					error(input); exit(100);
				}
				else
				{
					whatToSearch[x]++;
				}
			}
			for (int i = 0; i < 7; i++)
			{
				if (whatToSearch[i] >= 2)
				{
					error(input); exit(100);
				}
			}
			deleteNonUniqElements(whatToSearch);
			break;

		case 6: // exit
			while (head != NULL)
			{
				deleteElementFromDB(head);
			}
			for (int i = 0; i < lixCount; i++)
			{
				free(wrd[i]);
				freeCount++;
			}
			free(wrd);
			freeCount++;
			saveStats();
			exit(0);
		default:
			error(input);
			exit(100);
		}
	}
	for (int i = 0; i < lixCount; i++)
	{
		free(wrd[i]);
		freeCount++;
	}
	free(wrd);
	freeCount++;
}