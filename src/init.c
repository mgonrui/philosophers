#include "philo.h"
#include <pthread.h>

void init_program_data(t_program_data *program_data, char **argv)
{
	program_data->start_time = time_current();
	program_data->threads_running = 0;
	program_data->someone_died = false;
	program_data->nphilos = ft_mini_atol(argv[1]);
	program_data->time_to_die = ft_mini_atol(argv[2]);
	program_data->time_to_eat = ft_mini_atol(argv[3]);
	program_data->time_to_sleep = ft_mini_atol(argv[4]);
	if (argv[5] != NULL)
		program_data->max_nmeals = ft_mini_atol(argv[5]);
	else
		program_data->max_nmeals = -1;
	if (pthread_mutex_init(&program_data->read, NULL) != 0)
	{
		print_error("error initing mutex", 3);
		return;
	}
	if (pthread_mutex_init(&program_data->write, NULL))
	{
		print_error("error initing mutex", 3);
		return;
	}
	if (pthread_mutex_init(&program_data->eat, NULL) != 0)
	{
		print_error("error initing mutex", 3);
		return;
	}
	if (pthread_mutex_init(&program_data->death, NULL) != 0)
	{
		print_error("error initing mutex", 3);
		return;
	}

	return;
}

int init_philos(t_program_data *program_data)
{
	int i;

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
		program_data->philos[i]->last_meal_time = time_current();
		program_data->philos[i]->data = program_data;
		if (pthread_mutex_init(&program_data->philos[i]->mutex, NULL))
			return (print_error("Failed to init mutex", 2));
		i++;
	}
	return 0;
}

int init_forks(t_program_data *program_data)
{
	int i;

	program_data->forks = malloc(program_data->nphilos * sizeof(pthread_mutex_t));
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
	return 0;
}

void ft_destroy_forklst(t_program_data *data)
{
	int i;

	i = 0;
	while (i < data->nphilos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

void ft_destroy(t_program_data *data) // understood
{
	if (data->forks)
		ft_destroy_forklst(data);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->read);
	pthread_mutex_destroy(&data->write);
	// ft_free_prog(table);
}

int start_philo_threads(t_program_data *data)
{
	int		  i;
	pthread_t monitor;

	i = 0;
	if (pthread_create(&monitor, NULL, &ft_monitor, data))
		ft_destroy(data);
	while (i < data->nphilos)
	{
		if (pthread_create(&data->philos[i]->thread, NULL, &philo_actions, data->philos[i]))
			ft_destroy(data);
		i++;
	}
	pthread_join(monitor, NULL);
	i--;
	while (i >= 0)
	{
		pthread_join(data->philos[i]->thread, NULL);
		i--;
	}
	return 0;
}
