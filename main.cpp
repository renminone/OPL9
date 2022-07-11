#include <stdio.h>
#include <string.h>
#include <locale.h>
#define MAXL 100

int main()
{
    setlocale(LC_ALL, "Rus");
    FILE *fpin, *fpout;
    int i, j;
    int flag = 0;      //Проверка на повторяемость.
    int nc = 0;        //Счётчик неповторяющихся символов.
    int max = 0;       //Максимальное количество неповторяющихся элементов.
    int ns = 1;        //Счётчик строк.
    int str;           //Строка, в которой максимальное количество различных элементов.
    char line[MAXL];   //Строка на обработку.

    fopen_s(&fpin, "test.txt", "r");
    if (fpin == NULL)
        return; //Ошибка при открытии файла.

    fopen_s(&fpout, "result.txt", "w");
    if (fpout == NULL)
        return; //Ошибка при открытии файла.

    printf("Сканирование файла...\n\n");
    while (fgets(line, MAXL, fpin))
    {
        for (i = 0; i < strlen(line) - 2; i++)
        {
            for (j = 0; j < strlen(line) - 1; j++)
            {
                if (line[i] == line[j] && (i != j))  //В цикле проверяем каждый элемент строки на повторяемость.
                    flag = 1;
            }
            if (flag == 0)   //Если символ не повторяется.
                nc++;        //Счётчик увеличивается на 1.
            else
                flag = 0;
        }
        printf("Строка %d содержит %d различных символов.\n", ns, nc);
        if (max < nc)       //ищем максимальное кол-во неповторяемых символов
        {
            max = nc;       //Записываем, в какой строке наибольшее количество различных элементов.
            str = ns;       //записываем в какой строке max.
        }
        ns++;
        nc = 0;
    }
    ns = 1;
    fclose(fpin);

    printf("\nЗапись result.txt ...\n\n");
    fopen_s(&fpin, "test.txt", "r");
    if (fpin == NULL)
        return; // ошибка при открытии файла

    while (fgets(line, MAXL, fpin)) //Повторно считываем исходный файл.
    {
        if (ns != str)
            fputs(line, fpout);   //Печатаем его в выходной файл, кроме строки с max.
        ns++;
    }

    printf("Закрытие файлов...\n");
    fclose(fpin);
    fclose(fpout);
    return 0;
}
