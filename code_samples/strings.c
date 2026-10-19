#include <stdio.h>

// Массив - это стркутура данных одного и того же типа (массив int, массив char), расположенных в памяти последовательно (друг за другом), что позволяет обращаться к ним по индексам

// Пример 
// int array[4] = {10, 20, 30, 40};

// Строка в Си - это массив символов, заканчивающийся нулём '\0'

int main(int argc, char *argv[]) {
  char str0[] = {'a', 'b', 'c', '\0'};
  char str1[] = "abc";
  char *str = "abc";

  printf("%s\n", str);

  printf("%c\n", str[0]);
  printf("%c\n", str[1]);
  printf("%c\n", str[2]);
  printf("%d\n", str[3]);

  // str[0] = 'A';  // При изменении "char *" - ошибка Segmentation fault

  printf("%s\n", str);

  char *str_array[] = {"abc", "cat", "dog"};
  printf("%s\n", str_array[0]);
  printf("%s\n", str_array[1]);
  printf("%s\n", str_array[2]);

  return 0;
}
