struct Tovar
{
	char *Zv; //��������� - ������ �������
	int *Cod; //��� ������
	char *Name; //������������ ������
	int *Roz; //��������� ���� (��.)
	int *Opt; //������� ���� (��.)
};

struct Kateg
{
	char *Kat; // ��������� ������
	int *NumTov; //���������� ������� � ���������
	Tovar *tov;
};

struct Data
{
	int *NumKateg; //���������� ���������
	Kateg *kat;
};

struct Row
{
	char *Data;
};