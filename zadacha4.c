#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define     L                    4  // Количество бит в записи IP
#define     SIZE_DNS_NAME       10  // Длина DNS по умолчанию
#define     MAX_DNS_NAME       256  // Максимальная длина DNS
#define     EXIT_INPUT_ERROR    -2  // Признак аварийного завершения программы при сбое вызова scanf()
#define     EXIT_MEMORY_ERROR   -3  // Признак аварийного завершения программы при ошибки выделения памяти
#define     SUCCESS              0  // Признак успешного завершения программы

typedef struct server server;

struct server {                     // Структура "Сервер"
    char *dns;
    int ip[L];
    int count_proc;
    int count_core;
};

void free_serv(server* serv) {        // Освобождение памяти, выделенной под структуру
        free(serv->dns);
}

void standart_initial(server* serv) { // Инициализация по умолчанию
        memset(serv, 0, sizeof(serv));
}

int initial(server *serv, size_t n) {           // Инициализация значениями
    ptrdiff_t num = 0;
    while (true) {
        printf("Введите номер сервера, информацию о котором хотите внести. \nЕсли хотите завершить ввод, введите -1:\n");
        if (!(scanf("%zd", &num)))
            return EXIT_INPUT_ERROR;
        if (num == -1)                             // Проверка окончания ввода
            break;
        if ((num >= n) || (num < 0)) {             // Проверка корректности индекса
            printf("Значение должно быть от 0 до %zd!!!\n", n - 1);
            continue;
        }
        char buf[MAX_DNS_NAME];
        free(serv[num].dns);
        printf("Введите Domain Name сервера №%zd\n", num); // Ввод данных с проверками
        if (!(scanf("%s", buf)))
            return EXIT_INPUT_ERROR;
        serv[num].dns = realloc((&serv[num])->dns, strlen(buf) + 1);
        strcpy(serv[num].dns, buf);
        printf("Введите IP сервера №%zd\n", num);
        int flag = 1;
        while (flag) {
            if (!(scanf("%d%*c%d%*c%d%*c%d", &serv[num].ip[0], &serv[num].ip[1],
                    &serv[num].ip[2], &serv[num].ip[3])))
                return EXIT_INPUT_ERROR;
            if ((serv[num].ip[0] < 0) || (serv[num].ip[0] > 255)
                    || (serv[num].ip[1] < 0) || (serv[num].ip[1] > 255)
                    || (serv[num].ip[2] < 0) || (serv[num].ip[2] > 255)
                    || (serv[num].ip[3] < 0) || (serv[num].ip[3] > 255))
                printf("Значения должно каждого бита IP-адреса должно быть от 0 до 255. \nПовторите ввод IP адреса:\n");
            else
                flag = 0;
        }
        printf("Введите количество процессоров сервера №%zd\n", num);
        if (!(scanf("%d", &serv[num].count_proc)))
            return EXIT_INPUT_ERROR;
        printf("Введите количество ядер сервера №%zd\n", num);
        if (!(scanf("%d", &serv[num].count_core)))
            return EXIT_INPUT_ERROR;
        printf("\n");
    }
    return 0;
}

void swapserv(server* serv, ptrdiff_t n1, ptrdiff_t n2) { // Перестановка двух элементов массива серверов
    server temp = serv[n1];
    serv[n1] = serv[n2];
    serv[n2] = temp;
}

void quick_sort(server *serv, size_t n) {       // Сортировка массива серверов
    ptrdiff_t i = 0;
    ptrdiff_t j = n - 1;
    bool side = 0;
    while (i != j) {
        if (serv[i].ip[0] * 1000 + serv[i].ip[1]
                > serv[j].ip[0] * 1000 + serv[j].ip[1]) {
            swapserv(serv, i, j);
            side = !side;
        }
        if (side) {
            ++i;
        } else {
            --j;
        }
    }
    if (i > 1)
        quick_sort(serv, i);
    if (n > i + 1)
        quick_sort(serv + (i + 1), n - (i + 1));
}

//void print_serv(

void print_mas_serv(server *serv, ptrdiff_t n) {       // Печать массива серверов с разделением на подсети
    quick_sort(serv, n);                           // Сортировка массива серверов
    printf("Подсеть %d.%d:\n-----------------\n", serv[0].ip[0], serv[0].ip[1]);
    printf("Domain Name: %s\n", serv[0].dns);
    printf("IP: %d.%d.%d.%d\n", serv[0].ip[0], serv[0].ip[1], serv[0].ip[2],
            serv[0].ip[3]);
    printf("Количество процессоров %d\n", serv[0].count_proc);
    printf("Количество ядер %d\n\n", serv[0].count_core);
    for (size_t i = 1; i < n; i++) {
        if (!((serv[i].ip[0] == serv[i - 1].ip[0])
                && (serv[i].ip[1] == serv[i - 1].ip[1])))
            printf("Подсеть %d.%d:\n-----------------\n", serv[i].ip[0],
                    serv[i].ip[1]);
        printf("Domain Name: %s\n", serv[i].dns);
        printf("IP: %d.%d.%d.%d\n", serv[i].ip[0], serv[i].ip[1], serv[i].ip[2],
                serv[i].ip[3]);
        printf("Количество процессоров %d\n", serv[i].count_proc);
        printf("Количество ядер %d\n\n", serv[i].count_core);
    }
}

int main(void) {
    size_t n;                                            // Количество серверов
    printf("Введите количество серверов:\n");
    if (!(scanf("%zu", &n)))
        return EXIT_INPUT_ERROR;
    server *serv = (server*) malloc(n * sizeof(server)); // Выделение памяти под массив структур с проверкой
    if (serv == NULL) {
        printf("Ошибка выделения памяти\n");
        return EXIT_MEMORY_ERROR;
    }
    for (ptrdiff_t i = 0; i < n; i++)
        standart_initial(&serv[i]);                        // Заполнение значениями по умолчанию
    if (initial(serv, n) == EXIT_INPUT_ERROR) {            // Заполнение значениями с клавиатуры
        printf("Ошибка записи\n");
        return EXIT_INPUT_ERROR;
    }
    print_mas_serv(serv, n);                               // Печать массива структур
    for (ptrdiff_t i = 0; i < n; i++)
        free_serv(&serv[i]);
    free(serv);                                            // Освобождение памяти
    return SUCCESS;
}

