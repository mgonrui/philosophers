#include "philo.h"
#include <stdlib.h>


int main(int argc, char **argv)
{
	ft_check_input(argc, argv);
	t_philosopher philos[MAX_NPHILOS];
	pthread_mutex_t forks[MAX_NPHILOS];
	t_program_data *program_data;
	program_data = malloc(sizeof(t_program_data));
	init_program(program_data, argc, argv);
	init_forks(program_data, forks);
	return 0;
}
