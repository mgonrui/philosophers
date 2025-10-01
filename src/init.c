#include "philo.h"

void init_program_data(t_program_data *program_data, char **argv)
{
	program_data->someone_died = false;
	program_data->nphilos = ft_mini_atol(argv[1]);
	program_data->time_to_die = ft_mini_atol(argv[2]);
	program_data->time_to_eat = ft_mini_atol(argv[3]);
	program_data->time_to_sleep = ft_mini_atol(argv[4]);
	if (argv[5] != NULL)
		program_data->max_nmeals = ft_mini_atol(argv[5]);
	else
		program_data->max_nmeals = -1;
	return;
}

int init_philos(t_program_data *program_data)
{
	int i;

	i = 0;
	program_data->philos = malloc(program_data->nphilos * sizeof(t_philo));
	if (program_data->philos == NULL)
		return (print_error("No memory left to alloc", 2));
	while (i < program_data->nphilos)
	{
		program_data->philos[i] = malloc(sizeof(t_philo));
		if (program_data->philos[i] == NULL)
			return (print_error("No memory left to alloc", 2));
		program_data->philos[i]->id = i + 1;
		program_data->philos[i]->nmeals_eaten = 0;
		program_data->philos[i]->last_meal_time = get_current_time();
		// if (pthread_mutex_init(&data->philosophers[i]->l))
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
		i++;
	}
}

int start_philo_threads(t_program_data *data)
{
	int i;

	i = 0;
	while (i < data->nphilos)
	{
		if (pthread_create(&data->philos[i]->thread, NULL, &philo_actions, data->philos[i]))
			i++;
		usleep(100);
	}
}
