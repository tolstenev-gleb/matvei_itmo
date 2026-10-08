#!/bin/bash

set -u

PROG="./prg1"

check_case() {
    local input="$1"
    local expected="$2"
    local actual

    actual="$($PROG "$input")"

    if [ "$actual" != "$expected" ]; then
        echo "FAIL: input='$input'" 
        echo "expected:"
        echo "$expected"  
        echo "actual:"
        echo "$actual"    
        exit 1
    fi

    echo "OK: $input"
}

check_case "0" $'00000000 00000000\n00000000 00000000'
check_case "128" $'00000000 10000000\n00000000 10000000'
check_case "255" $'00000000 11111111\n11111111 00000000'
check_case "65535" $'11111111 11111111\n11111111 11111111'
check_case "220v" $'Ошибка: '\''220v'\'' не является числом.'

echo "All tests passed"
