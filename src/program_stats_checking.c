#include "philo.h"

bool philo_is_dead(t_program_data *data)
{
	int i = 0;
	while (i < data->nphilos)
	{
		pthread_mutex_lock(&data->eat);
		long time_since_meal = time_current() - data->philos[i]->last_meal_time;
		if (time_since_meal >= data->time_to_die)
		{
			print_action(data->philos[i], DIE);
			pthread_mutex_lock(&data->death);
			data->someone_died = true;
			pthread_mutex_unlock(&data->death);
			pthread_mutex_unlock(&data->eat);
			return true;
		}
		pthread_mutex_unlock(&data->eat);
		i++;
	}
	return false;
}

bool all_philos_are_full(t_program_data *data)
{
	int i;

	i = 0;
	while (i < data->nphilos)
	{
		if (data->philos[i]->nmeals_eaten < data->max_nmeals)
			return false;
		i++;
	}
	return true;
}

void *ft_monitor(void *vdata)
{
	t_program_data *data = (t_program_data *)vdata;

	while (true)
	{
		if (philo_is_dead(data))
			return NULL;

		if (data->max_nmeals != -1)
		{
			pthread_mutex_lock(&data->eat);
			bool all_full = all_philos_are_full(data);
			if (all_full)
			{
				pthread_mutex_lock(&data->death);
				data->someone_died = true;
				pthread_mutex_unlock(&data->death);
				pthread_mutex_unlock(&data->eat);
				return NULL;
			}
			pthread_mutex_unlock(&data->eat);
		}
	}
}
