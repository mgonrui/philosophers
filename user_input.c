#include "philosophers.h"

bool ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return true;
	return false;
}

void ft_error_exit(char *str, int errorcode)
{
	int i;
	i = 0;
	while(str[i] != '\0')
		write(2, &str[i++], 1);
	exit(errorcode);
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
	if (argc != 5)
		ft_error_exit("wrong number of parameters", 2);
	long nphilos = ft_mini_atol(argv[1]);
	printf("%ld\n", nphilos);
}
