#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INT_TYPE uint16_t

// Функция для проверки бита в числе по индексу
int get_bit(INT_TYPE value, size_t index) {
  int bit;
  INT_TYPE mask = 1 << index;
  INT_TYPE result = value & mask;
  if (result != 0) {
    bit = 1;
  } else {
    bit = 0;
  }
  return bit;
}

// Функция для получения байта по индексу
uint8_t get_byte(INT_TYPE value, int index) {
    INT_TYPE mask = 0b11111111;
    uint8_t byte = (value >> (8 * index)) & mask;
    return byte;
}

// Функция для проверки, является ли байт симметричным:
// совпадают 0 и 7 биты, совпадают 1 и 6 биты.
bool is_symmetric_byte(uint8_t byte) {
    bool answer;
    if (get_bit(byte, 0) == get_bit(byte, 7) &&
        get_bit(byte, 1) == get_bit(byte, 6)) {
        answer = true;
    } else {
        answer = false;
    }
    return answer;
}

// Печатает число в двоичном виде, байты разделяются пробелами.
void print_bits(INT_TYPE value) {
    size_t byte_count = sizeof(INT_TYPE);

    for (size_t index = 0; index < byte_count; index++) {
        uint8_t byte = get_byte(value, byte_count - 1 - index);

        for (int i = 7; i >= 0; i--) {
            printf("%d", get_bit(byte, i));
        }

        if (index + 1 < byte_count) {
            printf(" ");
        }
    }

    printf("\n");
}

// Для типа INT_TYPE выполняет преобразование по варианту 5-15:
// находит симметричные байты, а затем меняет их местами в обратном порядке.
INT_TYPE transform_number(INT_TYPE value) {
    size_t byte_count = sizeof(INT_TYPE);
    uint8_t bytes[byte_count];
    size_t positions[byte_count];
    size_t count = 0;

    for (size_t index = 0; index < byte_count; index++) {
        bytes[index] = get_byte(value, index);
    }

    for (size_t index = 0; index < byte_count; index++) {
        if (is_symmetric_byte(bytes[index])) {
            positions[count] = index;
            count++;
        }
    }

    INT_TYPE result = 0;

    if (count == 0 || count == 1) {
        result = value;
    } else {
        for (size_t index = 0; index < count / 2; index++) {
            size_t left = positions[index];
            size_t right = positions[count - 1 - index];
            uint8_t temp = bytes[left];
            bytes[left] = bytes[right];
            bytes[right] = temp;
        }

        for (size_t index = 0; index < byte_count; index++) {
            result = result | ((INT_TYPE)(bytes[index] << (8 * index)));
        }
    }
    return result;
}

bool parse_uint(const char *text, INT_TYPE *value) {
    char *end = NULL;
    unsigned long long parsed = 0u;

    errno = 0;
    parsed = strtoull(text, &end, 10);

    if (errno != 0 || end == text || *end != '\0') {
        return false;
    }

    if (parsed > (INT_TYPE)-1) {
        return false;
    }

    *value = (INT_TYPE)parsed;
    return true;
}

int main(int argc, char *argv[]) {
    INT_TYPE value;
    char *programm_name = argv[0];
    char *string_number = argv[1];
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [число]\n", programm_name);
        return EXIT_FAILURE;
    }

    if (argc == 2) {
        if (false == parse_uint(string_number, &value)) {
            fprintf(stderr, "Ошибка: '%s' не является числом.\n", argv[1]);
            return EXIT_FAILURE;
        }
    } else {
        srand(time(NULL));
        value = (INT_TYPE)rand();
    }

    print_bits(value);

    value = transform_number(value);

    print_bits(value);

    return EXIT_SUCCESS;
}