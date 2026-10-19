#include <stdio.h>

// Компилировать gcc arg.c -o prog

// -o задаёт имя программы

// пример запуска - ./prog abcdef 123

int main(int argc, char *argv[]) {

  printf("%d\n", argc);  // количество переданных аргументов

  printf("%s\n", argv[0]);  // нулевой аргумент - имя программы prog
  printf("%s\n", argv[1]);  // первый аргумент - abcdef
  printf("%s\n", argv[2]);  // второй аргумент - 123

  return 0;
}
