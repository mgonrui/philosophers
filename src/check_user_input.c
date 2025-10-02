/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_user_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariogo2 <mariogo2@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:49:20 by mariogo2          #+#    #+#             */
/*   Updated: 2025/10/02 23:51:21 by mariogo2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

long	mini_atol(char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (is_digit(str[i]) && str[i] != '\0')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result);
}

int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (argc != 5 && argc != 6)
	{
		return (print_error("Wrong number of arguments\n", 2), 1);
	}
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (is_digit(argv[i][j]) == false || mini_atol(argv[i]) == 0)
			{
				print_error("Arguments must be integers greater than zero\n",
					2);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
