NAME = philo

COMPILER = cc
FLAGS = -Wall -Wextra -Werror -pthread -fsanitize=undefined  -fsanitize=thread -g -Wunreachable-code

_CLEAN = rm -rf

SRC = philo.c parsing.c ft_atoi.c thread_func.c object_init.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

%.o:%.c philo.h
	$(COMPILER) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(COMPILER) $(FLAGS) $(OBJ) -o $@

clean:
	$(_CLEAN) $(OBJ)

fclean: clean
	$(_CLEAN) $(NAME)

re: fclean $(NAME)

.PHONY: clean
