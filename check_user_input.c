#include "philo.h"

bool ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return true;
	return false;
}

long ft_mini_atol(char *str)
{
	long result;
	int i;

	result = 0;
	i = 0;
	while(str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += str[i] - '0';
			i++;
		}
		else
			ft_error_exit("wrong input", 1);
	}
	return result;
}

void ft_check_input(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		ft_error_exit("wrong number of parameters", 2);
}
