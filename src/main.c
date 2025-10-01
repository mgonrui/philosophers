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

bool are_all_threads_running(t_program_data *data, long *threads, long philo_nbr)
{
	bool ret;
	ret = false;

	pthread_mutex_lock(&data->read);
	if (*threads == philo_nbr)
		ret = true;
	pthread_mutex_unlock(&data->read);
	return ret;
}

int main(int argc, char **argv)
{
	t_program_data data;

	if (check_input(argc, argv))
		return 1;
	init_program_data(&data, argv);
	if (init_philos(&data) != 0)
	{
		print_error("error initing philos", 2);
		return 1;
	}
	if (init_forks(&data) != 0)
	{
		print_error("error initing forks", 2);
		return 1;
	}
	// if (has_someone_died(&data) == false)
	// {
	start_philo_threads(&data);
	// }
	usleep(100);
	// ft_thread_join(&data);
	return 0;
}
