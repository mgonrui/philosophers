/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_stats_checking.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariogo2 <mariogo2@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:49:23 by mariogo2          #+#    #+#             */
/*   Updated: 2025/10/02 23:51:24 by mariogo2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_is_dead(t_data *data)
{
	int		i;
	long	time_since_meal;

	i = 0;
	while (i < data->nphilos)
	{
		pthread_mutex_lock(&data->eat);
		time_since_meal = time_current() - data->philos[i]->last_meal_time;
		pthread_mutex_unlock(&data->eat);
		if (time_since_meal >= data->time_to_die)
		{
			print_action(data->philos[i], DIE);
			pthread_mutex_lock(&data->mtx_end);
			data->end_program = true;
			pthread_mutex_unlock(&data->mtx_end);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	all_philos_are_full(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nphilos)
	{
		if (data->philos[i]->nmeals_eaten < data->max_nmeals)
			return (false);
		i++;
	}
	return (true);
}

void	*arbiter(void *vdata)
{
	t_data	*data;

	data = (t_data *)vdata;
	while (true)
	{
		usleep(1000);
		if (philo_is_dead(data))
			return (NULL);
		if (data->max_nmeals != -1)
		{
			pthread_mutex_lock(&data->eat);
			if (all_philos_are_full(data) == true)
			{
				pthread_mutex_lock(&data->mtx_end);
				data->end_program = true;
				pthread_mutex_unlock(&data->mtx_end);
				pthread_mutex_unlock(&data->eat);
				return (NULL);
			}
			pthread_mutex_unlock(&data->eat);
		}
	}
}
