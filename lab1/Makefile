.PHONY: all clean debug

NAME = prg1mamN3149
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(NAME).c
	gcc -o $(NAME) $(CFLAGS) $(NAME).c

debug: $(NAME).c
	gcc -o $(NAME) $(CFLAGS) -g $(NAME).c

test: $(NAME)

test16: $(NAME)
	./test_uint16.sh

test32: $(NAME)
	./test_uint32.sh

test64: $(NAME)
	./test_uint64.sh

clean:
	rm $(NAME)

