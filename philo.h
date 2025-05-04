#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>
#include <unistd.h>

#define MAX_NPHILOS 500

typedef struct s_philo
{
	unsigned int id;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	bool is_dead;
	bool is_eating;
	unsigned int start_time;
	unsigned int last_meal_time;
	unsigned int nmeals_eaten;
} t_philo;

typedef struct s_program_data
{
	bool is_dead;
	int nphilos;
	int time_to_die;
	int time_to_sleep;
	int time_to_eat;
	int max_nmeals;
	pthread_mutex_t lock_write;
	pthread_mutex_t lock_dead;
	pthread_mutex_t lock_meal;
	t_philo *philos;
} t_program_data;

// check user input
void ft_check_input(int argc, char **argv);
long ft_mini_atol(char *str);

// utils
void ft_error_exit(char *str, int errorcode);
size_t	get_current_time(void);

// init
//
void init_prog(t_program_data *program_data, char **argv, t_philo *philos,
	pthread_mutex_t *forks);

void init_philos(t_philo *philos, t_program_data *program_data,
				 pthread_mutex_t *forks);
void init_fork_mutexes(t_program_data *program_data, pthread_mutex_t *forks);
#endif // PHILOSOPHERS_H
