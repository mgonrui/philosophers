#include "philo.h"

int print_error(char *str, int errorcode)
{
	int i;
	i = 0;
	write(2, "Error: ", 8);
	while (str[i] != '\0')
		write(2, &str[i++], 1);
	return (errorcode);
}

size_t get_current_time(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		print_error("gettimeofday function error\n", 3);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
