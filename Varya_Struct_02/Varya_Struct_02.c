// Varya_Struct_02.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "parcer.h"

int main()
{
	time_t now = time(NULL);
	int stroks[99];

	for (int i = 0; i < 99; i++)
		stroks[i] = i % 3 == 1 ? 1 : 0;

	/*putElementToDB("Ulanovsky", "George", 2, 4, &now, &now, stroks);
	putElementToDB("Ulanovsky", "George", 2, 1, &now, &now, stroks);
	putElementToDB("Ulanovsky", "George", 3, 1, &now, &now, stroks);


	putElementToDB("Ulanovsky", "George", 2, 4, &now, &now, stroks);
	putElementToDB("Ulanovsky", "George", 2, 1, &now, &now, stroks);
	putElementToDB("Ulanovsky", "George", 2, 1, &now, &now, stroks);
	putElementToDB("Ulanovsky", "George", 3, 1, &now, &now, stroks);

	putElementToDB("Baranova", "Varvara", 2, 1, &now, &now, stroks);
	putElementToDB("Baranova", "Varvara", 2, 4, &now, &now, stroks);
	putElementToDB("Baranova", "Varvara", 2, 3, &now, &now, stroks);

	putElementToDB("Fidarov", "German", 2, 2, &now, &now, stroks);

	putElementToDB("Fidarov", "German", 2, 2, &now, &now, stroks);

	printDataBase();*/

	//printf("uniq:%d \n", deleteNonUniqElements());

	char selects[7] = { 0, 5, 3, -1, -1, -1, -1 };

	Condition a = { moreEqual, 2, 0, NULL, 0, NULL };
	Condition* conditions[7] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL };
	/*printf("\nselect:%d \n", selectFunc(selects, conditions));
	printf("\nupdate:%d \n", updateFunc("TeStNaMe", NULL, -1, -1, NULL, NULL, NULL, conditions));
	printf("\nselect:%d \n", selectFunc(selects, conditions));*/

	printDataBase();
	parceLine("insert last_nm=Ulanovsky, first_nm=George, curse_id=2, lab_id=1, start_tm=2000.10.10!22:1:20, end_tm=2000.10.10!23:40:23, result=[]");

	//parceLine("insert last_nm=Baranova, first_nm=Genya, curse_id=3, lab_id=6, start_tm=2000.10.10!22:1:20, end_tm=2000.10.10!23:0:20, result=[]");
	parceLine("insert last_nm=Ulanovsky, first_nm=George, curse_id=2, lab_id=2, start_tm=2000.10.10!22:1:20, end_tm=2000.10.10!23:0:20, result=[]");
	parceLine("insert last_nm=Ulanovsky, first_nm=George, curse_id=1, lab_id=3, start_tm=2000.10.10!22:1:20, end_tm=2000.10.10!23:0:20, result=[]");
	parceLine("insert last_nm=Ulanovsky, first_nm=George, curse_id=2, lab_id=4, start_tm=2000.10.10!22:1:20, end_tm=2000.10.10!23:0:20, result=[]");
	parceLine("insert last_nm=Ulanovsky, first_nm=George, curse_id=3, lab_id=5, start_tm=2000.10.10!22:1:20, end_tm=2000.10.10!23:0:20, result=[]");
	parceLine("insert last_nm=Ulanovsky, first_nm=Grisha, curse_id=3, lab_id=6, start_tm=2000.10.10!22:1:20, end_tm=2000.10.10!23:0:20, result=[]");
	printDataBase();
	printDataBase();
	parceLine("uniq first_nm");
	printDataBase();
	char line[] = "curse_id>=3";
	parceCondition(line, conditions);
	printf("\nselect:%d \n", selectFunc(selects, conditions));
	parceLine("exit");


	saveStats();
}