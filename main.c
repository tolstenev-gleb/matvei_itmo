#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INT_TYPE uint32_t

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

// Для типа INT_TYPE выполняет преобразование по варианту 5-15:
// находит симметричные байты, а затем меняет их местами в обратном порядке.
INT_TYPE transform_number(INT_TYPE value) {
    int byte_count = sizeof(INT_TYPE);
    uint8_t bytes[byte_count];  // cоздание массива отдельных байтов
    int positions[byte_count];  // позиции (индексы / номера) симметричных байтов
    int count = 0;

    // разбиваем число на байты и сохраняем их по отдельности в массив
    for (int number = 0; number < byte_count; number++) {
        bytes[number] = get_byte(value, number);
    }

    // проверяем байты по отдельности на симметричность и номера симметричных байтов сохраняем в массив positions
    for (int number = 0; number < byte_count; number++) {
        if (proverka(bytes[number]) == 1) {
            positions[count] = number;
            count = count + 1;
        }
    }

    INT_TYPE result = 0;

    if (count == 0 || count == 1) {
        result = value;
    } else {
        // Упорядочивает массив bytes согласно заданию (делает перестановку)
        for (int number = 0; number < count / 2; number++) {
            int left = positions[number];
            int right = positions[count - 1 - number];
            // Перестановка через временную переменную
            uint8_t temp = bytes[left];
            bytes[left] = bytes[right];
            bytes[right] = temp;
        }

        for (int number = 0; number < byte_count; number++) {
            // printf("number: %d\n", number);
            // printf("bytes[%d]: %d\n", number, bytes[number]);
            // print_bits(bytes[number]);
            // printf("8 * %d: %d\n", number, 8 * number);
            // printf("  byte: ");
            // print_bits(bytes[number] << (8 * number));

            result = result | ((INT_TYPE)(bytes[number] << (8 * number)));
            
            // printf("result: ");
            // print_bits(result);
            printf("\n");
        }
    }
    return result;
}

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

int main(int argc, char *argv[]) {
    INT_TYPE value;
    bool status;
    char *programm_name = argv[0];
    char *string_number = argv[1];
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [число]\n", programm_name);
        return EXIT_FAILURE;
    }

    if (argc == 2) {
        status = parse_uint(string_number, &value);
        if (status == false) {
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