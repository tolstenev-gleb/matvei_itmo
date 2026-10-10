#include <stdio.h>

// Массив - это стркутура данных одного и того же типа (массив int, массив char), расположенных в памяти последовательно (друг за другом), что позволяет обращаться к ним по индексам

// Пример 
// int array[4] = {10, 20, 30, 40};

// Строка в Си - это массив символов, заканчивающийся нулём '\0'

int main(int argc, char *argv[]) {
  // char str0[] = {'a', 'b', 'c', '\0'};
  // char str1[] = "abc";
  // char *str1 = "abc";

  // printf("%s\n", str1);

  // printf("%c\n", str1[0]);
  // printf("%c\n", str1[1]);
  // printf("%c\n", str1[2]);
  // printf("%d\n", str1[3]);

  // str1[0] = 'A';

  // printf("%s\n", str1);

  // char *str_array[] = {"abc", "cat", "dog"};
  // printf("%s\n", str_array[0]);
  // printf("%s\n", str_array[1]);
  // printf("%s\n", str_array[2]);

  printf("%d\n", argc);
  printf("%s\n", argv[0]);
  printf("%s\n", argv[1]);
  printf("%s\n", argv[2]);

}

