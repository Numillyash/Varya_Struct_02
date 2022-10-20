// Varya_Struct_02.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "parcer.h"

int main()
{
	char** words = NULL;
	getWordsAndCount("insert       car_vendor=kia, car_model=light,  car_year=2009, car_id=M785FF, divise=cam  carrying=21, axles=10", words);
	/*time_t now = time(NULL);
	char *stroks[20] = { "Test 1", "Test 2", "Test 3", "Test 4"};
	putElementToDB("Ulanovsky", "George", 2, 4, &now, &now, stroks, 3);
	putElementToDB("Ulanovsky", "George", 2, 1, &now, &now, stroks, 3);
	putElementToDB("Ulanovsky", "George", 3, 1, &now, &now, stroks, 3);
	time_t now = time(NULL);
	int stroks[99];

	for (int i = 0; i < 99; i++)
		stroks[i] = i % 3 == 1 ? 1 : 0;

	putElementToDB("Ulanovsky", "George", 2, 4, &now, &now, stroks);
	putElementToDB("Ulanovsky", "George", 2, 1, &now, &now, stroks);
	putElementToDB("Ulanovsky", "George", 2, 1, &now, &now, stroks);
	putElementToDB("Ulanovsky", "George", 3, 1, &now, &now, stroks);

	putElementToDB("Baranova", "Varvara", 2, 1, &now, &now, stroks);
	putElementToDB("Baranova", "Varvara", 2, 4, &now, &now, stroks);
	putElementToDB("Baranova", "Varvara", 2, 3, &now, &now, stroks);

	putElementToDB("Fidarov", "German", 2, 2, &now, &now, stroks);

	putElementToDB("Fidarov", "German", 2, 2, &now, &now, stroks);

	printDataBase();

	printf("uniq:%d \n", deleteNonUniqElements());

	char selects[7] = { 0, 5, 3, -1, -1, -1, -1 };

	Condition a = { moreEqual, 2, 0, NULL, 0, NULL };
	Condition* conditions[7] = {NULL, NULL, NULL, &a, NULL, NULL, NULL};
	printf("\nselect:%d \n", selectFunc(selects, conditions));
	printf("\nupdate:%d \n", updateFunc("TeStNaMe", NULL, -1, -1, NULL, NULL, NULL, conditions));
	printf("\nselect:%d \n", selectFunc(selects, conditions));

	printDataBase();*/
	saveStats();
}