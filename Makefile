NAME = philo
CC = gcc
CFILES =  	src/main.c \
			src/utils.c \
			src/time_utils.c \
			src/check_user_input.c \
			src/program_stats_checking.c \
			src/philo_actions.c \
			src/init.c \

OFILES = $(CFILES:.c=.o)

%.o : %.c philo.h
	$(CC) -Wall -Wextra -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) -Wall -Wextra $(OFILES) -o $(NAME)

clean:
	@ rm -f $(OFILES)

fclean: clean
	@ rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
