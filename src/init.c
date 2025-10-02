/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariogo2 <mariogo2@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:49:21 by mariogo2          #+#    #+#             */
/*   Updated: 2025/10/02 23:51:22 by mariogo2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

int	init_program_data(t_data *program_data, char **argv)
{
	program_data->end_program = false;
	program_data->nphilos = mini_atol(argv[1]);
	program_data->time_to_die = mini_atol(argv[2]);
	program_data->time_to_eat = mini_atol(argv[3]);
	program_data->time_to_sleep = mini_atol(argv[4]);
	if (argv[5] != NULL)
		program_data->max_nmeals = mini_atol(argv[5]);
	else
		program_data->max_nmeals = -1;
	if (pthread_mutex_init(&program_data->mtx_print, NULL))
	{
		return (print_error("error initing mutex", 3));
	}
	if (pthread_mutex_init(&program_data->eat, NULL) != 0)
	{
		return (print_error("error initing mutex", 3));
	}
	if (pthread_mutex_init(&program_data->mtx_end, NULL) != 0)
	{
		return (print_error("error initing mutex", 3));
	}
	program_data->start_time = time_current();
	return (0);
}

int	init_philos(t_data *program_data)
{
	int	i;

	i = 0;
	program_data->philos = malloc(program_data->nphilos * sizeof(t_philo *));
	if (program_data->philos == NULL)
		return (print_error("No memory left to alloc", 2));
	while (i < program_data->nphilos)
	{
		program_data->philos[i] = malloc(sizeof(t_philo));
		if (program_data->philos[i] == NULL)
			return (print_error("No memory left to alloc", 2));
		program_data->philos[i]->id = i + 1;
		program_data->philos[i]->nmeals_eaten = 0;
		program_data->philos[i]->last_meal_time = program_data->start_time;
		program_data->philos[i]->data = program_data;
		if (pthread_mutex_init(&program_data->philos[i]->mutex, NULL))
			return (print_error("Failed to init mutex", 2));
		i++;
	}
	return (0);
}

int	init_forks(t_data *program_data)
{
	int	i;

	program_data->forks = malloc(program_data->nphilos
			* sizeof(pthread_mutex_t));
	if (program_data->forks == NULL)
		return (print_error("No memory left to alloc", 2));
	i = 0;
	while (i < program_data->nphilos)
	{
		if (pthread_mutex_init(&program_data->forks[i], NULL))
			return (print_error("Could not create fork mutex", 3));
		program_data->philos[i]->l_fork = &program_data->forks[i];
		if (i == program_data->nphilos - 1)
			program_data->philos[i]->r_fork = &program_data->forks[0];
		else
			program_data->philos[i]->r_fork = &program_data->forks[i + 1];
		i++;
	}
	return (0);
}

int	start_philo_threads(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	if (pthread_create(&monitor, NULL, &arbiter, data))
		cleanup(data);
	while (i < data->nphilos)
	{
		if (pthread_create(&data->philos[i]->thread, NULL, &philo_actions,
				data->philos[i]))
			cleanup(data);
		i++;
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->nphilos)
	{
		pthread_join(data->philos[i]->thread, NULL);
		i++;
	}
	return (0);
}
