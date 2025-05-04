NAME = philo
CC = gcc
CFILES =  	main.c \
			init.c \
			check_user_input.c

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
