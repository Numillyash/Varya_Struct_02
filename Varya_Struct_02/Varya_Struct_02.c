// Varya_Struct_02.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "db_struct.h"

int main()
{
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

	char selects[7] = { 1, 5, 3, -1, -1, -1, -1 };

	Condition a = { moreEqual, 2, 0, NULL, 0, NULL };
	Condition* conditions[7] = {NULL, NULL, NULL, &a, NULL, NULL, NULL};
	printf("\nselect:%d \n", selectFunc(selects, conditions));

	//printDataBase();

}