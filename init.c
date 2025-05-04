#include "philo.h"

void init_prog(t_program_data *program_data, char **argv, t_philo *philos,
	pthread_mutex_t *forks)
{
	program_data->is_dead = false;
	program_data->nphilos = ft_mini_atol(argv[1]);
	program_data->time_to_die = ft_mini_atol(argv[2]);
	program_data->time_to_eat = ft_mini_atol(argv[3]);
	program_data->time_to_sleep = ft_mini_atol(argv[4]);
	if (argv[5] != NULL)
		program_data->max_nmeals = ft_mini_atol(argv[5]);
	else
		program_data->max_nmeals = -1;
	pthread_mutex_init(&program_data->lock_dead, NULL);
	pthread_mutex_init(&program_data->lock_write, NULL);
	pthread_mutex_init(&program_data->lock_meal, NULL);
	init_fork_mutexes(program_data, forks);
	init_philos(philos, program_data, forks);
	return ;
}

void init_philos(t_philo *philos, t_program_data *program_data,
				 pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < program_data->nphilos)
	{
		philos[i].id = i;
		philos[i].is_eating = false;
		philos[i].nmeals_eaten = 0;
		philos[i].start_time = get_current_time();
		philos[i].last_meal_time = get_current_time();
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[program_data->nphilos - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
	return ;
}

void init_fork_mutexes(t_program_data *program_data, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < program_data->nphilos)
		pthread_mutex_init(&forks[i++], NULL);
	return ;
}
