NAME = philo_bonus

COMPILER = cc
FLAGS = -Wall -Wextra -Werror -pthread

_CLEAN = rm -rf

SRC =	philo_bonus.c parsing_bonus.c ft_atoi_bonus.c ft_time_bonus.c \
		utils_bonus.c object_init_bonus.c child_routing.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

%.o:%.c philo_bonus.h
	$(COMPILER) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(COMPILER) $(FLAGS) $(OBJ) -o $@

clean:
	$(_CLEAN) $(OBJ)

fclean: clean
	$(_CLEAN) $(NAME)

re: fclean $(NAME)

.PHONY: clean
