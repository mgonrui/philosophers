/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariogo2 <mariogo2@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 23:15:28 by mariogo2          #+#    #+#             */
/*   Updated: 2025/10/02 23:51:25 by mariogo2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	has_someone_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mtx_end);
	if (philo->data->end_program == true)
	{
		pthread_mutex_unlock(&philo->data->mtx_end);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->mtx_end);
	return (false);
}

void	*philo_actions(void *vphilo)
{
	t_philo	*philo;

	philo = vphilo;
	if (philo->id % 2 == 0)
		my_usleep(10);
	if (philo->data->nphilos == 1)
	{
		print_action(philo, GRAB_FORK);
		my_usleep(philo->data->time_to_die);
		return (NULL);
	}
	while (has_someone_died(philo) == false)
	{
		if (has_someone_died(philo) == false)
			action_eat(philo);
		if (has_someone_died(philo) == false)
			action_sleep(philo);
		if (has_someone_died(philo) == false)
			action_think(philo);
	}
	return (NULL);
}

int	print_action(t_philo *philo, t_actions action)
{
	pthread_mutex_lock(&philo->data->mtx_end);
	if (philo->data->end_program == true)
		return (pthread_mutex_unlock(&philo->data->mtx_end), 0);
	if (action == DIE)
		return (action_die(philo), 0);
	pthread_mutex_unlock(&philo->data->mtx_end);
	pthread_mutex_lock(&philo->data->mtx_print);
	if (action == GRAB_FORK)
		printf("%ld %d has taken a fork\n",
			time_passed(philo->data->start_time), philo->id);
	else if (action == EAT)
		printf("%ld %d is eating\n", time_passed(philo->data->start_time),
			philo->id);
	else if (action == THINK)
		printf("%ld %d is thinking\n", time_passed(philo->data->start_time),
			philo->id);
	else if (action == SLEEP)
		printf("%ld %d is sleeping\n", time_passed(philo->data->start_time),
			philo->id);
	pthread_mutex_unlock(&philo->data->mtx_print);
	return (0);
}
