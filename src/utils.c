/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariogo2 <mariogo2@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:49:22 by mariogo2          #+#    #+#             */
/*   Updated: 2025/10/02 23:51:22 by mariogo2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *str, int errorcode)
{
	int	i;

	i = 0;
	write(2, "Error: ", 8);
	while (str[i] != '\0')
		write(2, &str[i++], 1);
	return (errorcode);
}
