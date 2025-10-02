NAME = philo
CC = gcc
CFILES =  	src/main.c \
			src/utils.c \
			src/time_utils.c \
			src/check_user_input.c \
			src/program_stats_checking.c \
			src/philo_actions.c \
			src/init.c \
			src/routine.c \

OFILES = $(CFILES:.c=.o)
CFLAGS		= -Wall -Wextra -Werror

%.o : %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME)

clean:
	@ rm -f $(OFILES)

fclean: clean
	@ rm -f $(NAME)
#
# saddress: CFLAGS += -fsanitize=address -g
# saddress: re
#
# # Thread Sanitizer (data races)
# sthread: CFLAGS += -fsanitize=thread -g
# sthread: re
re: fclean all

.PHONY: all clean fclean re bonus
