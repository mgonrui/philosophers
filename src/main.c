/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariogo2 <mariogo2@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:49:21 by mariogo2          #+#    #+#             */
/*   Updated: 2025/10/02 23:51:24 by mariogo2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void	cleanup(t_data *data) // understood
{
	int i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nphilos)
			pthread_mutex_destroy(&data->forks[i++]);
	}
	pthread_mutex_destroy(&data->mtx_end);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->mtx_print);
	i = 0;
	while (i < data->nphilos)
		free(data->philos[i++]);
	free(data->philos);
	free(data->forks);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (check_input(argc, argv))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
	{
		print_error("Failed to allocate program data", 2);
		return (1);
	}
	init_program_data(data, argv);
	if (init_philos(data) != 0)
	{
		print_error("error initing philos", 2);
		return (1);
	}
	if (init_forks(data) != 0)
	{
		print_error("error initing forks", 2);
		return (1);
	}
	start_philo_threads(data);
	cleanup(data);
	return (0);
}
