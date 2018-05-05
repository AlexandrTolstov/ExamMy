#include <math.h>
#include <string>
#include <string.h>
#include "Price.h"

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

/* ��������� �� ������ Row ������� � ������� Start �� ���������� ������� ';', ����������� � int � ���������� �������� � Num � ���������� �������� �������.*/
int IndWriteRow(int Start, char *Row, int *Num)
{
	char *Mass = (char*)malloc(sizeof(char));

	int i = Start;
	int j = 0;

	while (*(Row + i) != ';')
	{
		if (*(Row + i + 1) == '\0') break;
		*(Mass + j) = *(Row + i) - 48;
		i++;
		j++;
		Mass = (char*)realloc(Mass, sizeof(char)*(j + 1));
	}
	Mass = (char*)realloc(Mass, sizeof(char)*(j + 1));
	*(Mass + j) = '\0';

	int Sum1 = 0;
	int Chislo = 0;
	int w = 0;

	while (w < j)
	{
		Chislo = (int)(pow(10, ((double)(j - w)))*(*(Mass + w)));
		Sum1 += Chislo;
		w++;
	}
	Sum1 /= 10;
	*Num = Sum1;

	return i;

	free(Mass);
}

/*��������� �� ������ Row ������� � ������� Start �� ���������� ������� ';', ���������� � Mass ����������� � ���������� �������� �������*/
int IndWriteRowChar(int Start, char *Row, char *Mass)
{
	char *temp = (char*)malloc(sizeof(char));

	int i = Start;
	int j = 0;

	while (*(Row + i) != ';')
	{
		if (*(Row + i) == '\0') break;
		*(temp + j) = *(Row + i);
		i++;
		j++;
		temp = (char*)realloc(temp, sizeof(char)*(j + 1));
	}
	temp = (char*)realloc(temp, sizeof(char)*(j + 1));
	*(temp + j) = '\0';

	strcpy(Mass, temp);
	free(temp);

	return i;
}

/*����� ������ � ���������*/
void VivodStruct(Data *data)
{
	printf("���������� �������� NumKat = %d\n\n", *data->NumKateg);

	for (size_t i = 0; i < *data->NumKateg; i++)
	{
		printf("\n��������� �%d --%s | ���-�� � ��������� N = %d\n\n", i + 1, data->kat[i].Kat, *data->kat[i].NumTov);

		for (size_t j = 0; j < (*data->kat[i].NumTov); j++)
		{
			printf("�%d\t", j + 1);
			printf(" %c ", data->kat[i].tov[j].Zv[0]);
			printf(" %d ", *data->kat[i].tov[j].Cod);
			printf(" %s ", data->kat[i].tov[j].Name);
			printf(" %d ", *data->kat[i].tov[j].Roz);
			printf(" %d \n", *data->kat[i].tov[j].Opt);
		}
	}
}

/*�������� ����� ������ � ���������*/
void NewRow(Data *data)
{
	printf("�������� ����� ������\n");
	printf("----------------------------------------------\n");
	printf("�������� ��������� �� ���������� ������ ������� �������:\n\n");

	int VibKat = 0;

	int NumKat = *data->NumKateg;

	for (size_t i = 0; i < NumKat; i++)
	{
		printf("%d = %s", i + 1, data->kat[i].Kat);
	}

	printf("\n������� ����� ���������\n");
	printf("N = ");

	scanf("%d", &VibKat);
	while (VibKat <= 0 || VibKat > *data->NumKateg)
	{
		printf("\n�� ������� �������� ����� ���������.\n���������� ������\nN = ");
		scanf("%d", &VibKat);
	}

	for (size_t i = 0; i < NumKat; i++)
	{
		if ((VibKat - 1) == i)
		{
			int CodTov = 0;
			int NumTov = *data->kat[i].NumTov; // ���������� ������� � ���������
			char Str[150];

			/*�������������� ������*/
			data->kat[i].tov = (Tovar*)realloc(data->kat[i].tov, sizeof(Tovar)*(NumTov + 1));
			data->kat[i].tov[NumTov].Zv = (char*)malloc(sizeof(char));
			data->kat[i].tov[NumTov].Cod = (int*)malloc(sizeof(int));
			data->kat[i].tov[NumTov].Name = (char*)malloc(sizeof(char));
			data->kat[i].tov[NumTov].Roz = (int*)malloc(sizeof(int));
			data->kat[i].tov[NumTov].Opt = (int*)malloc(sizeof(int));

			data->kat[i].tov[NumTov].Zv[0] = ' ';

			/*��� ������*/
			printf("\n��� ������\nCod = ");
			scanf("%d", &CodTov);
			getchar(); //��� ��������� ������ ����� (��� ����� �� �������� fgets)
			*data->kat[i].tov[NumTov].Cod = CodTov;

			/*��� ������*/
			printf("\n������������ ������\nName = ");
			fgets(Str, sizeof(Str), stdin);

			int z = 0;
			while (Str[z] != '\n')
			{
				data->kat[i].tov[NumTov].Name = (char*)realloc(data->kat[i].tov[NumTov].Name, sizeof(char)*(z + 1));
				data->kat[i].tov[NumTov].Name[z] = Str[z];
				z++;
			}
			data->kat[i].tov[NumTov].Name[z] = '\0';

			/*���� ���������*/
			int Price = 0;
			printf("\n���� ��������� \nPriceRoz = ");
			scanf("%d", &Price);
			getchar();
			*data->kat[i].tov[NumTov].Roz = Price;

			/*���� �������*/
			Price = 0;
			printf("\n���� ������� \nPriceRoz = ");
			scanf("%d", &Price);
			getchar();
			*data->kat[i].tov[NumTov].Opt = Price;

			*data->kat[i].NumTov += 1;
		}
	}
}

/*�������� ����� �� �����*/
void DeletRow(Data *data)
{
	printf("�������� ������\n");
	printf("----------------------------------------------\n");
	printf("�������� ��������� �� ���������� ������ ������� �������:\n\n");

	int VibKat = 0;

	int NumKat = *data->NumKateg;

	for (size_t i = 0; i < NumKat; i++)
	{
		printf("%d = %s", i + 1, data->kat[i].Kat);
	}

	printf("\n������� ����� ���������\n");
	printf("N = ");

	scanf("%d", &VibKat);
	while (VibKat <= 0 || VibKat > *data->NumKateg)
	{
		printf("\n�� ������� �������� ����� ���������.\n���������� ������\nN = ");
		scanf("%d", &VibKat);
	}

	for (size_t i = 0; i < NumKat; i++)
	{
		if ((VibKat - 1) == i)
		{
			for (size_t j = 0; j < *data->kat[i].NumTov; j++)
			{
				printf("�%d - %d  %s\n", j + 1, *data->kat[i].tov[j].Cod, data->kat[i].tov[j].Name);
			}

			int VibTov = 0;
			int NamTovar = *data->kat[i].NumTov;
			printf("\n������� ����� ������ ��� ��������\n");
			printf("N = ");

			scanf("%d", &VibTov);
			while (VibKat <= 0 || VibTov > NamTovar)
			{
				printf("\n�� ������� �������� ����� ������.\n���������� ������\nN = ");
				scanf("%d", &VibTov);
			}

			for (size_t j = VibTov - 1; j < NamTovar; j++)
			{
				if ((VibTov - 1) == j && j < NamTovar - 1)
				{
					for (size_t z = j; z < (NamTovar - 1); z++)
					{
						data->kat[i].tov[z].Zv = data->kat[i].tov[z + 1].Zv;
						*data->kat[i].tov[z].Cod = *data->kat[i].tov[z + 1].Cod;
						//data->kat[i].tov[j].Name = (char*)realloc(data->kat[i].tov[j].Name, sizeof(char)*(strlen(data->kat[i].tov[j + 1].Name)));

						data->kat[i].tov[z].Name = data->kat[i].tov[z + 1].Name;
						*data->kat[i].tov[z].Roz = *data->kat[i].tov[z + 1].Roz;
						*data->kat[i].tov[z].Opt = *data->kat[i].tov[z + 1].Opt;
					}

					*data->kat[i].NumTov -= 1;
					data->kat[i].tov = (Tovar*)realloc(data->kat[i].tov, sizeof(Tovar)*(NamTovar - 1));
				}
				else if ((VibTov - 1) == j)
				{
					*data->kat[i].NumTov -= 1;
					data->kat[i].tov = (Tovar*)realloc(data->kat[i].tov, sizeof(Tovar)*(NamTovar - 1));
				}
			}
		}
	}
}

/*������ ��������� � ����*/
void WriteToFile(Data *data, Row *row) // Row ��������� ������
{
	row = (Row*)realloc(row, sizeof(Row));

	int NumOfRow = 0;

	for (size_t i = 0; i < (*data->NumKateg); i++)
	{
		row = (Row*)realloc(row, sizeof(Row)*(NumOfRow + 1));
		int g = 0; //�������
		int Size = strlen(data->kat[i].Kat);
		(row + NumOfRow)->Data = (char*)malloc(sizeof(char)*(Size + 5));

		(row + NumOfRow)->Data[0] = (row + NumOfRow)->Data[1] = ';';
		g = 2;

		int z = 0;
		while (z < Size)
		{
			(row + NumOfRow)->Data[g] = data->kat[i].Kat[z];
			g++;
			z++;
		}
		g--;
		(row + NumOfRow)->Data[g] = (row + NumOfRow)->Data[g + 1] = ';';
		(row + NumOfRow)->Data[g + 2] = '\0';

		//printf("%s\n", (row + NumOfRow)->Data);
		NumOfRow++;

		for (size_t j = 0; j < *data->kat[i].NumTov; j++)
		{
			row = (Row*)realloc(row, sizeof(Row)*(NumOfRow + 1));
			(row + NumOfRow)->Data = (char*)malloc(sizeof(char)*150);

			sprintf((row + NumOfRow)->Data, "%c;%d;%s;%d;%d", *data->kat[i].tov[j].Zv, *data->kat[i].tov[j].Cod, data->kat[i].tov[j].Name, *data->kat[i].tov[j].Roz, *data->kat[i].tov[j].Opt);
			//printf("%s\n", (row + NumOfRow)->Data);
			NumOfRow++;
		}
	}

	/*for (size_t i = 0; i < NumOfRow; i++)
	{
		printf("%d - %s\n", i, (row + i)->Data);
	}*/
	
	FILE *file;

	if ((file = fopen("pprice.csv", "w")) == NULL)
		printf("���� ���������� ������� ��� �������\n");
	else {
		for (size_t i = 0; i < NumOfRow; i++) {

			fprintf(file, "%s\n", (row + i)->Data);
		}
	}
	fclose(file);
}