#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INT_TYPE uint16_t

// Функция для проверки бита в числе по номеру
int get_bit(INT_TYPE value, size_t number) {
  int bit;
  INT_TYPE mask = 1 << number;
  INT_TYPE result = mask & value;
  if (result != 0) {
    bit = 1;
  } else {
    bit = 0;
  }
  return bit;
}

// Функция для получения байта по номеру
uint8_t get_byte(INT_TYPE value, int number) {
    INT_TYPE mask = 0b11111111;
    uint8_t byte = (value >> (8 * number)) & mask;
    return byte;
}

// Функция для проверки, является ли байт симметричным:
// совпадают 0 и 7 биты, совпадают 1 и 6 биты.
bool proverka(uint8_t byte) {
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

    for (size_t number = 0; number < byte_count; number++) {
        uint8_t byte = get_byte(value, byte_count - 1 - number);

        for (int i = 7; i >= 0; i--) {
            printf("%d", get_bit(byte, i));
        }

        if (number + 1 < byte_count) {
            printf(" ");
        }
    }

    printf("\n");
}

INT_TYPE set_byte(INT_TYPE value, uint8_t byte, int number) {
    INT_TYPE mask = (INT_TYPE)0xFF << (8 * number);

    value = value & ~mask;
    value = value | ((INT_TYPE)byte << (8 * number));

    return value;
}

// Для типа INT_TYPE выполняет преобразование по варианту 5-15:
// находит симметричные байты, а затем меняет их местами в обратном порядке.
INT_TYPE transform_number(INT_TYPE value) {
    INT_TYPE result = value;
    int left_index = 0;
    int right_index = sizeof(INT_TYPE) - 1;

    while (left_index < right_index) {
        while (left_index < right_index &&
               false == proverka(get_byte(value, left_index)))
        {
            left_index++;
        }

        while (left_index < right_index &&
               false == proverka(get_byte(value, right_index)))
        {
            right_index--;
        }

        if (left_index < right_index)
        {
            uint8_t left_byte = get_byte(value, left_index);
            uint8_t right_byte = get_byte(value, right_index);

            result = set_byte(result, right_byte, left_index);
            result = set_byte(result, left_byte, right_index);

            left_index++;
            right_index--;
        }
    }
    return result;
}

// Переводит число из строки text в INT_TYPE, записывает его по указателю ptr_value,
// и возвращает статус: true - успешное преобразование, false - ошибка
bool parse_uint(const char *text, INT_TYPE *ptr_value) {
    char *end = NULL;
    unsigned long long parsed_number = 0u;

    errno = 0;
    parsed_number = strtoull(text, &end, 10);

    if (errno != 0 || end == text || *end != '\0') {
        // errno будет не нулевым (конкретно значение ERANGE), если был указан знак минуса в исходном числе, то возвращается абсолютное значение результата преобразования. Если абсолютное значение вызовет "переполнение", то устанавливается ERANGE

        // end == text - в строке вообще нет цифр

        // *end != '\0' - если цифры есть, но попались другие символы (не цифры)

        return false;
    }

    if (parsed_number > (INT_TYPE)-1) { // (INT_TYPE)-1 - максимально возможное число (все биты в единице)
        return false;
    }

    *ptr_value = (INT_TYPE)parsed_number;
    return true;
}

// argc - argument counter - счётчик аргументов

int main(int argc, char *argv[]) {
    INT_TYPE value = 0;
    bool status;
    char *programm_name = argv[0];
    char *string_number = argv[1];

    // запуск программы без числа - argc равно 1 (аргумент - только имя программы)
    if (argc == 1)
    {
        // то генерируем
        srand(time(NULL));
        value = (INT_TYPE)rand();
    }
    else if (argc == 2)  // запуск программы с 2 аргументами - имя программы и кандидат на число 
    {
        status = parse_uint(string_number, &value);
        if (status == false)
        {
            fprintf(stderr, "Ошибка: '%s' не является числом.\n", string_number);
            return EXIT_FAILURE;
        }
    }
    else // запуск программы с 3 и более аргументами - ошибка использования программы
    {
        fprintf(stderr, "Usage: %s [число]\n", programm_name);
        return EXIT_FAILURE;
    }
    
    print_bits(value);

    value = transform_number(value);

    print_bits(value);

    return EXIT_SUCCESS;
}