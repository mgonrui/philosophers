#include "philo.h"
#include <stdlib.h>

static void ft_thread_join(t_program_data *data)
{
	int i;

	i = 0;
	while (i < data->nphilos)
	{
		pthread_join(data->philos[i]->thread, NULL);
		i++;
	}
}

void cleanup(t_program_data *data) // understood
{
	int i;

	if (data->forks)
	{
		i = 0;
		while (i < data->nphilos)
			pthread_mutex_destroy(&data->forks[i++]);
	}
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->eat);
	pthread_mutex_destroy(&data->print);

	i = 0;
	while (i < data->nphilos)
		free(data->philos[i++]);
	free(data->philos);
	free(data->forks);
	free(data);
}

int main(int argc, char **argv)
{
	t_program_data *data;

	if (check_input(argc, argv))
		return 1;
	data = malloc(sizeof(t_program_data));
	if (!data)
	{
		print_error("Failed to allocate program data", 2);
		return 1;
	}
	init_program_data(data, argv);
	if (init_philos(data) != 0)
	{
		print_error("error initing philos", 2);
		return 1;
	}
	if (init_forks(data) != 0)
	{
		print_error("error initing forks", 2);
		return 1;
	}
	start_philo_threads(data);
	cleanup(data);
	return 0;
}
