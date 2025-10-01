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
