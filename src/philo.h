#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define MAX_NPHILOS 200

typedef struct s_program_data
{
	struct s_philo **philos;
	bool			 someone_died;
	long			 nphilos;
	unsigned int	 start_time;
	long			 time_to_die;
	long			 time_to_sleep;
	long			 time_to_eat;
	long			 max_nmeals;
	pthread_mutex_t *forks;
	pthread_mutex_t	 read;
	pthread_mutex_t	 write;
} t_program_data;

typedef struct s_philo
{
	unsigned int	 id;
	bool			 is_dead;
	unsigned int	 last_meal_time;
	unsigned int	 nmeals_eaten;
	pthread_t		 thread;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
} t_philo;

// check user input
int	 check_input(int argc, char **argv);
long ft_mini_atol(char *str);

// utils
int	   print_error(char *str, int errorcode);
size_t get_current_time(void);

// main
void init_program_data(t_program_data *program_data, char **argv);
int	 init_forks(t_program_data *program_data);
int	 init_philos(t_program_data *program_data);
int	 start_philo_threads(t_program_data *data);

// philo_actions
void *philo_actions(void *philo);

#endif // PHILOSOPHERS_H
