#include "philo.h"

bool is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

long ft_mini_atol(char *str)
{
	long result;
	int	 i;

	result = 0;
	i = 0;
	while (is_digit(str[i]) && str[i] != '\0')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return result;
}

int check_input(int argc, char **argv)
{
	int i = 1;
	int j = 0;
	if (argc != 5 && argc != 6)
	{
		print_error("Wrong number of arguments\n", 2);
		return 1;
	}
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (is_digit(argv[i][j]) == false || ft_mini_atol(argv[i]) == 0)
			{
				print_error("Arguments must be integers greater than zero\n", 2);
				return 1;
			}
			j++;
		}
		i++;
	}
	return 0;
}
