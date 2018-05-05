#include <stdio.h>
#include <time.h>
#include <string.h>
#include <Windows.h>
#include <locale.h>
#include <math.h>

#include "Price.h"
#include "Function.h"

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

FILE *price; // Переменная, в которую будет помещен указатель на созданный поток данных 

void main()
{
	srand(time(NULL));

	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Data *data = (Data*)malloc(sizeof(Data));
	data->NumKateg = (int*)malloc(sizeof(int));

	data->kat = (Kateg*)malloc(sizeof(Kateg));
	//Kateg *kateg = (Kateg*)malloc(sizeof(Kateg));

	Row *row = (Row*)malloc(sizeof(Row));

	/*for (size_t i = 0; i < 256; i++)
	{
		printf("%d - %c\n", i, i);
	}*/

#pragma region Считывание данных с фала и помещении их в структуру ROW 

	char *estr; //Указатель, в который будет помещен адрес массива, в который считана строка, или NULL если достигнут коней файла или произошла ошибка

	price = fopen("pprice.csv", "r");

	int i = 0;
	while (1)
	{
		row = (Row*)realloc(row, (i + 1) * sizeof(Row));
		(row + i)->Data = (char*)malloc(sizeof(char) * 150);

		estr = fgets((row + i)->Data, sizeof(char)*150, price); //Данные из потока price размером sizeof(char)*150 записываются в (row + i)->Data
		
		//printf("%d - %s \n",i+1, (row + i)->Data);
		/*int LenthOfRow = strlen((row + i)->Data);
		(row + i)->Data[LenthOfRow - 4] = '\0';*/
		

		if (estr == NULL)
		{
			if (feof(price) != 0)
				break;
			else
			{
				printf("\nОшибка чтения из файла\n");
				break;
			}
		}
		i++;
	}
	if (fclose(price) == EOF) printf("ошибка\n");

#pragma endregion Считывание данных с фала и помещении их в структуру ROW  

#pragma region Считывание данных с фала и помещении их в структуру Tovar

	//printf("Открытие файла");

	int z = i;
	int InKat = 0; // Количество категорий
	int InTov = 0; // Количество товаров

	int k = 0;
	int l = 0;

	int *temp = (int*)malloc(sizeof(char));
	int Sum = 0;

	for (size_t i = 0; i < z; i++)
	{
		if (((row + i)->Data[0] == ';') && ((row + i)->Data[1] == ';'))
		{
			data->kat = (Kateg*)realloc(data->kat, sizeof(Kateg)*(InKat + 1));
			data->kat[InKat].tov = (Tovar*)malloc(sizeof(Tovar));
			data->kat[InKat].Kat = (char*)malloc(sizeof(char));
			
			while (row[i].Data[k] != '\0' || ((row[i].Data[k] != ';') && (row[i].Data[k + 1] != ';') && (row[i].Data[k + 2] != ';') && (row[i].Data[k + 3] != ';')))
			{
				if (row[i].Data[k] != '\;')
				{
					data->kat[InKat].Kat[l] = row[i].Data[k];
					l++;
					data->kat[InKat].Kat = (char*)realloc(data->kat[InKat].Kat, sizeof(char)*(l + 1));
				}
				k++;
			}
			l = 0;
			k = 0;

			//printf("%d - %s \n",i+1,  data->kat[InKat].Kat);

			data->kat[InKat].NumTov = (int*)malloc(sizeof(int));

			InKat++;
			InTov = 0;
		}
		else
		{
			data->kat[InKat - 1].tov = (Tovar*)realloc(data->kat[InKat - 1].tov, sizeof(Tovar)*(InTov + 1));

			/*Звездочка*/
			data->kat[InKat - 1].tov[InTov].Zv = (char*)malloc(sizeof(char));
			data->kat[InKat - 1].tov[InTov].Zv[0] = (row + i)->Data[0];

			int g = 2; //Строковая каретка
			int k = 0;

			/*Код товара*/
			/*Преобразование строки кода товара в Код типа Int*/
			data->kat[InKat - 1].tov[InTov].Cod = (int*)malloc(sizeof(int));
			g = IndWriteRow(g, (row + i)->Data, data->kat[InKat - 1].tov[InTov].Cod);
			//printf("%d - %d \n", i + 1, *data->kat[InKat - 1].tov[InTov].Cod);
			g++;

			/*Наименование*/
			int z = g;
			while (row[i].Data[z] != 59) // Определение количества элементав в строке до символа ';'
			{
				z++;
				k++;
			}
			data->kat[InKat - 1].tov[InTov].Name = (char*)malloc(sizeof(char)*k);
			g = IndWriteRowChar(g, (row + i)->Data, data->kat[InKat - 1].tov[InTov].Name);
			g++;

			/*Рознечная цена*/
			data->kat[InKat - 1].tov[InTov].Roz = (int*)malloc(sizeof(int));
			g = IndWriteRow(g, (row + i)->Data, data->kat[InKat - 1].tov[InTov].Roz);	
			g++;

			/*Оптовая цена*/
			data->kat[InKat - 1].tov[InTov].Opt = (int*)malloc(sizeof(int));
			g = IndWriteRow(g, (row + i)->Data, data->kat[InKat - 1].tov[InTov].Opt);
			g++;

			InTov++;
			*data->kat[InKat - 1].NumTov = InTov;
		}
	}

	*data->NumKateg = InKat;

#pragma endregion Считывание данных с фала и помещении их в структуру Tovar

#pragma region Основная программа

	while (1)
	{
		int VibMenu = 0;
		printf("________________________________________________________\n");
		printf("Выберети действие:\n");
		printf("Добавление записи в прайс: 1\n");
		printf("Удаление записи из прайса: 2\n");
		printf("Распечатка прайса: 3\n");
		printf("________________________________________________________\n");

		printf("Menu = ");
		scanf("%d", &VibMenu);
		printf("\n");

		while (VibMenu <= 0 || VibMenu > 3)
		{
			printf("Вы ввели неверный пункт меню.\nПопробуйте снова\nMenu = ");
			scanf("%d", &VibMenu);
			printf("\n");
		}

		switch (VibMenu)
		{
		case 1:
		{
			NewRow(data);
			WriteToFile(data, row);
			break;
		}
		case 2:
		{
			DeletRow(data);
			WriteToFile(data, row);
			break;
		}
		case 3: 
		{
			VivodStruct(data);
			break;
		}
		default:
			break;
		}

		printf("\n________________________________________________________\n");
		printf("Желаете продолжить? (Y/N): ");
		char YesNo = ' ';
		getchar();
		scanf("%c", &YesNo);

		if (YesNo != 'Y' && YesNo != 'y') break;
		printf("\n________________________________________________________\n");
		system("cls");
	}

#pragma endregion Основная программа

	free(temp);
	free(data);
	free(row);

	system("pause");
}