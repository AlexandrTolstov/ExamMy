struct Tovar
{
	char *Zv; //Звездочка - первый столбец
	int *Cod; //Код товара
	char *Name; //Наименование товара
	int *Roz; //Розничная цена (тг.)
	int *Opt; //Оптовая цена (тг.)
};

struct Kateg
{
	char *Kat; // Категория товара
	int *NumTov; //Количество товаров в категории
	Tovar *tov;
};

struct Data
{
	int *NumKateg; //Количество категорий
	Kateg *kat;
};

struct Row
{
	char *Data;
};