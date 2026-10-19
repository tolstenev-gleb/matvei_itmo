.PHONY: all clean debug

NAME = prg1mamN3149
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(NAME).c
	gcc -o $(NAME) $(CFLAGS) $(NAME).c

debug: $(NAME).c
	gcc -o $(NAME) $(CFLAGS) -g $(NAME).c

clean:
	rm $(NAME)

