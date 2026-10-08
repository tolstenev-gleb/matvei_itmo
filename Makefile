.PHONY: all clean debug test archive

# TODO
# добавить суффикс к имени программы согласно варианту
# Петр Сергеевич Иванов
# группа — N31451
# prg1psiN31451

NAME = prg1
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): main.c
	gcc -o $(NAME) $(CFLAGS) main.c

debug: main.c
	gcc -o $(NAME) $(CFLAGS) -g main.c

test: $(NAME)
	./test.sh

archive: clean
	tar -czf $(NAME).tar.gz main.c Makefile README.txt

clean:
	rm -f $(NAME) $(NAME).tar.gz

