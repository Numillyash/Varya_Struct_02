// Varya_Struct_02.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "db_struct.h"

int main()
{
	time_t now = time(NULL);
	char *stroks[20] = { "Test 1", "Test 2", "Test 3", "Test 4"};
	putElementToDB("Ulanovsky", "George", 2, 4, &now, &now, stroks, 3);
	putElementToDB("Ulanovsky", "George", 2, 1, &now, &now, stroks, 3);
	putElementToDB("Ulanovsky", "George", 3, 1, &now, &now, stroks, 3);

	putElementToDB("Baranova", "Varvara", 2, 1, &now, &now, stroks, 2);

	putElementToDB("Fidarov", "German", 2, 2, &now, &now, stroks, 4);

	printDataBase();

	deleteElementsWithParametres("Ulanovsky", NULL, NULL, 1, NULL, NULL, NULL, NULL);

	printDataBase();

}