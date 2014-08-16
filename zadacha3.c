#define     MEMORY_ERROR      -3  // Признак аварийного завершения программы при сбое при выделении памяти
#define     MAX_LENGTH_STR    256 // Максимальное количество символов в строке
#define     MAX_LENTH_NAME    30  // Максимальная длина переменной
#define     MAX_LENTH_INDEX   30  // Максимальная длина индекса
FUCK USA!!!
FUCK EU!!!



I HATE EVERYTHING ABOUT YOU!!!
size_t change_index(char **str, ptrdiff_t n, char ***r) {      // Функция, выполняющая преобразование индексной арифметики в адресную
    size_t count = 0;                                          // Количество строк в результирующей структуре
    char** res = NULL;                                         // Результирующий вектор векторов
    char buf_index[MAX_LENTH_INDEX];                           // Буфер для записи индекса
    char inverse_buf_name[MAX_LENTH_NAME];                     // Буфер для записи инверсии имени
    int flag1, flag2;                                          // Признаки нахождения "[" и "]"
    for (ptrdiff_t i = 0; i < n; i++) {
        flag1 = 0;
        flag2 = 0;
        ptrdiff_t index=0;                                     // Индекс "[" в строке
        for (ptrdiff_t j = 0; j < strlen(str[i]); j++) {
            if (str[i][j] == '[') {
                index = j;
                flag1 = 1;
            }
            if ((str[i][j] == ']') && (flag1 == 1))
                flag2 = 1;
        }
        if ((flag1 == 1) && (flag2 == 1)) {                    // Если в строке найдены "[" и "]"
            char *c_index;                                     // Указатель на название индекса
            char *c_name;                                      // Указатель на имя переменной
            count++;
            ptrdiff_t k = 0;                                   // Счетчик
            for (ptrdiff_t j = index + 1; str[i][j] != ']'; j++, k++)                  // Поиск и запись индекса
                buf_index[k] = str[i][j];
            //buf_index[k] = '\0';
            c_index = (char*) malloc((strlen(buf_index) + 1) * sizeof(char));	       // Выделение памяти под индекс с проверкой
            if (c_index == NULL)
                return MEMORY_ERROR;
            for (ptrdiff_t j = 0; j <= strlen(buf_index); j++)
                c_index[j] = buf_index[j];
            k = 0;
            for (ptrdiff_t j = index - 1;                                              // Поиск и запись имени переменной
                    (str[i][j] != ' ') && (str[i][j] != '(') && (j > -1);
                    j--, k++)
                inverse_buf_name[k] = str[i][j];
            inverse_buf_name[k] = '\0';
            k = strlen(inverse_buf_name);
            c_name = (char*) malloc((k+1) * sizeof(char));                           // Выделение памяти под имя переменной с проверкой
            if (c_name == NULL)
                return MEMORY_ERROR;
            for (ptrdiff_t j = 0; j < k + 1; j++) {printf("VHOD  ");
                c_name[j] = inverse_buf_name[k - j];}
            printf("\nINVERSE_NAME =    %s      k=%zd     name=%s    len=%zu\n", inverse_buf_name, k,c_name,strlen(c_name));
            res = (char **) realloc(res, (count) * sizeof(char*));                // Расширение выделенной под результирующую структуру памяти
            if (res == NULL)
                return MEMORY_ERROR;
            size_t symbol_res = strlen(str[i]) + 4;
            res[count - 1] = (char*) malloc((symbol_res + 1) * sizeof(char));     // Выделение памяти под строки рещультирующей структуры
            if (res[count - 1] == NULL)
                return MEMORY_ERROR;
            strncat(res[count - 1], str[i], index - strlen(c_name));              // Запись строки в необходимом виде
            res[count - 1][index - strlen(c_name)] = '*';
            res[count - 1][index - strlen(c_name) + 1] = '(';
            strncat(res[count - 1], c_name, strlen(c_name));
            res[count - 1][index + 2] = ' ';
            res[count - 1][index + 3] = '+';
            res[count - 1][index + 4] = ' ';
            strncat(res[count - 1], c_index, strlen(c_index));
            res[count - 1][index + strlen(c_index) + 5] = ')';
            printf("\nS=       %s   \nName=    %s     \nIndex=     %s\n",res[count-1], c_name, c_index);
            for (k = 0;
                    (str[i][index + strlen(c_index) + 2 + k] != '\0')
                            && (str[i][index + strlen(c_index) + 2 + k] != '\n');
                    k++)
                res[count - 1][index + strlen(c_index) + 6 + k] = str[i][index
                        + strlen(c_index) + 2 + k];
            res[count - 1][index + strlen(c_index) + 6 + k] = '\0';
            free(c_index);
            free(c_name);
        }
    }
    *r = res;
    return count;
}

void print_res(char **res, int n) {                                  // Вывод результата
    for (ptrdiff_t i=0; i<n; i++)
        puts(res[i]);
}

int main(int argc, char* argv[]) {
    char **res = NULL;                                               // Указатель на результирующую структуру
    ptrdiff_t n = 0;                                                 // Количество строк
    char* test;
    char s[MAX_LENGTH_STR];                                          // Буфер
    char **str = NULL;                                               // Указатель на структуру, куда будет записан файл
    if (argc != 2) {                                                 // Проверка количества аргументов
        printf("Ошибка входных данных\n");
        return INPUT_ERROR;
    }
    FILE *text = fopen(argv[1], "r");                                // Открытие файла с проверкой
    if (text == NULL) {
        printf("Ошибка открытия файла\n");
        return READ_ERROR;
    }
    while (!feof(text)) {                                            // Подсчет количества строк в файле
        if (!(fgets(s, MAX_LENGTH_STR, text)&&feof(text)))
            n++;
        else {
            printf("Ошибка чтения из файла");
            return READ_ERROR;
        }
    }
    str = (char **) malloc(n * sizeof(char*));                       // Выделение памяти под структуру, куда будет записан файл
    if (str == NULL) {
        printf("Ошибка памяти\n");
        return MEMORY_ERROR;
    }
    for (size_t i = 0; i < n; ++i) {                           
        str[i] = (char *) malloc(MAX_LENGTH_STR * sizeof(char));
        if (str[i] == NULL) {
            printf("Ошибка памяти\n");
            return MEMORY_ERROR;
        }
    }
        rewind(text);
        for (ptrdiff_t i = 0; i < n-1; i++)                          // Запись файла в str
            if (fgets(str[i], MAX_LENGTH_STR, text) == NULL) {
                printf("Ошибка чтения\n");
                return READ_ERROR;
            }
        size_t count = 0;
        if ((count = change_index(str, n, &res)) != MEMORY_ERROR)    // Функция изменения индексной арифметики в адресную
            printf("%zu\n", count);
        else {
            printf("Ошибка памяти\n");
            return MEMORY_ERROR;
        } 
        print_res(res, count);                                 // Вывод результата
        for (ptrdiff_t i = 0; i < n; i++)                      // Освобождение памяти, выделенной под структуру под файл
            free(str[i]);
        free(str);
        for (ptrdiff_t i = 0; i < count; i++)                  // Освобождение памяти, выделенной под результирующую структуру
            free(res[i]);
        free(res);
        fclose(text);                                          // Закрытие текстового файла
        return SUCCESS;
    }

