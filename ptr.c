#include <stdio.h>

int func(int a, int *ptr_qube) {
  printf("ptr_qube: %p\n", ptr_qube); // & - взятие адреса

  int s = a * a;
  int q = a * a * a;
  *ptr_qube = q;
  return s;
}

int main() {
  int value;

  value = 42;

  printf(" value: %d\n", value);
  printf("&value: %p\n", &value); // & - взятие адреса
  printf("\n");

  int *ptr = &value;

  printf("   ptr: %p\n", ptr);
  printf("  *ptr: %d\n", *ptr);  // * - разыменование указателя
  printf("\n");

  int qube;
  printf("&qube: %p\n", &qube); // & - взятие адреса

  int result = func(value, &qube);

  printf("result: %d\n", result);
  printf("  qube: %d\n", qube);

  return 0;
}