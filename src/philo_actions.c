#include "philo.h"
#include <pthread.h>
#include <unistd.h>

void print_action(t_philo *philo, t_actions action)
{

	pthread_mutex_lock(&philo->data->death);
	if (philo->data->someone_died == true)
	{
		pthread_mutex_unlock(&philo->data->death);
		return;
	}

	if (action == DIE)
	{
		philo->data->someone_died = true;
		pthread_mutex_unlock(&philo->data->death);

		pthread_mutex_lock(&philo->data->print);
		printf("%ld %d died\n", time_passed(philo->data->start_time), philo->id);
		pthread_mutex_unlock(&philo->data->print);
		return;
	}
	pthread_mutex_unlock(&philo->data->death);

	pthread_mutex_lock(&philo->data->print);
	if (action == GRAB_FORK)
		printf("%ld %d has taken a fork\n", time_passed(philo->data->start_time), philo->id);
	else if (action == EAT)
		printf("%ld %d is eating\n", time_passed(philo->data->start_time), philo->id);
	else if (action == THINK)
		printf("%ld %d is thinking\n", time_passed(philo->data->start_time), philo->id);
	else if (action == SLEEP)
		printf("%ld %d is sleeping\n", time_passed(philo->data->start_time), philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void ft_grab_forks(t_philo *p)
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

void action_eat(t_philo *philo)
{

	ft_grab_forks(philo);
	print_action(philo, EAT);
	pthread_mutex_lock(&philo->data->eat);
	philo->last_meal_time = time_current();
	philo->nmeals_eaten++;
	pthread_mutex_unlock(&philo->data->eat);
	my_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void action_sleep(t_philo *philo)
{
	print_action(philo, SLEEP);
	my_usleep(philo->data->time_to_sleep);
}

void action_think(t_philo *philo)
{
	print_action(philo, THINK);
	my_usleep(TIME_TO_THINK);
}

bool has_someone_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->someone_died == true)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (false);
}

void *philo_actions(void *vphilo)
{
	t_philo *philo;

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
	return NULL;
}
