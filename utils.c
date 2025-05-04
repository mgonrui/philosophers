#include "philo.h"

void ft_error_exit(char *str, int errorcode)
{
	int i;
	i = 0;
	write(2, "Error: ", 8);
	while(str[i] != '\0')
		write(2, &str[i++], 1);
	exit(errorcode);
}


size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_error_exit("gettimeofday function error\n", 3);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
