NAME = philo_bonus

COMPILER = cc
FLAGS = -Wall -Wextra -Werror -pthread

_CLEAN = rm -rf

SRC =	philo_bonus.c parsing_bonus.c ft_atoi_bonus.c ft_time_bonus.c clean_up_bonus.c \
		utils_bonus.c object_init_bonus.c child_routing_bonus.c monitoring_bonus.c generate_names_bonus.c

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