#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Проверка запуска с переменной среды, включающей отладочный вывод.
    // Пример запуска с установкой переменной LAB1DEBUG в 1:
    // $ LAB1DEBUG=1 ./lab1abcNXXXXX 123
    char *DEBUG = getenv("LAB1DEBUG");
    if (DEBUG) {
        fprintf(stderr, "Включен вывод отладочных сообщений\n");
    }
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [число]\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    //
    // Тут может быть ваш код. В этом файле Вы можете поменять все, что угодно.
    // Главное - чтобы потом все правильно работало ;-)
    //
    
    return EXIT_SUCCESS;
}
