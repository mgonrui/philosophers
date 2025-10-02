/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariogo2 <mariogo2@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:49:23 by mariogo2          #+#    #+#             */
/*   Updated: 2025/10/02 23:51:23 by mariogo2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

void	action_grab_forks(t_philo *p)
{
	if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->r_fork);
		print_action(p, GRAB_FORK);
		pthread_mutex_lock(p->l_fork);
		print_action(p, GRAB_FORK);
	}
	else
	{
		pthread_mutex_lock(p->l_fork);
		print_action(p, GRAB_FORK);
		pthread_mutex_lock(p->r_fork);
		print_action(p, GRAB_FORK);
	}
}

void	action_eat(t_philo *philo)
{
	action_grab_forks(philo);
	print_action(philo, EAT);
	pthread_mutex_lock(&philo->data->eat);
	philo->last_meal_time = time_current();
	philo->nmeals_eaten++;
	pthread_mutex_unlock(&philo->data->eat);
	my_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	action_die(t_philo *philo)
{
	philo->data->end_program = true;
	pthread_mutex_unlock(&philo->data->mtx_end);
	pthread_mutex_lock(&philo->data->mtx_print);
	printf("%ld %d died\n", time_passed(philo->data->start_time), philo->id);
	pthread_mutex_unlock(&philo->data->mtx_print);
}

void	action_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	my_usleep(philo->data->time_to_sleep);
}

void	action_think(t_philo *philo)
{
	print_action(philo, THINK);
	my_usleep(TIME_TO_THINK);
}
