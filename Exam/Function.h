/* ��������� �� ������ Row ������� � ������� Start �� ���������� ������� ';', ����������� � int � ���������� �������� � Num � ���������� �������� �������.*/
int IndWriteRow(int Start, char *Row, int *Num);
/*��������� �� ������ Row ������� � ������� Start �� ���������� ������� ';', ���������� � Mass ����������� � ���������� �������� �������*/
int IndWriteRowChar(int Start, char *Row, char *Mass);
/*����� ������ � ���������*/
void VivodStruct(Data *data);
/*�������� ����� ������*/
void NewRow(Data *data);
/*������ ��������� � ����*/
void WriteToFile(Data *data, Row *row);