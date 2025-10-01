#include "philo.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (check_input(argc, argv))
		return 1;

	t_program_data data;
	init_program_data(&data, argv);
	if (init_philos(&data) != 0)
		return 1;
	if (init_forks(&data) != 0)
		return 1;
	// t_philosopher philos[MAX_NPHILOS];
	// pthread_mutex_t forks[MAX_NPHILOS];
	// program_data = malloc(sizeof(t_program_data));
	// init_program(program_data, argc, argv);
	// init_forks(program_data, forks);
	return 0;
}
