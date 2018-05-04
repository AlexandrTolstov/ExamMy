/* Считывает из строки Row начиная с позиции Start до следующего символа ';', преобразует в int и записывает значение в Num и возвращает конечную позицию.*/
int IndWriteRow(int Start, char *Row, int *Num);
/*Считывает из строки Row начиная с позиции Start до следующего символа ';', записывает в Mass посимвольно и возвращает конечную позицию*/
int IndWriteRowChar(int Start, char *Row, char *Mass);
/*Вывод данных в структуре*/
void VivodStruct(Data *data);
/*Создание новой записи*/
void NewRow(Data *data);
/*Запись Структуры в файл*/
void WriteToFile(Data *data, Row *row);