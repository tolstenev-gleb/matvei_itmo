#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

int main() {
  srand(time(NULL));  // seed random - запускает генератор псевдослучайных чисел ОТ переданного числа
                      // time(NULL) возвращает количество секунд, прошедших с 1 января 1970
  int r = rand();  // получение очередного случайного числа int из генератора

  printf("%d\n", r);
  printf("%u\n", (uint16_t)r);  // явное приведение числа int к типу uint16_t
  
  return 0;
}
