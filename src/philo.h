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
#define TIME_TO_THINK 2

typedef enum e_actions
{
	GRAB_FORK,
	EAT,
	THINK,
	SLEEP,
	DIE,
} t_actions;

typedef struct s_program_data
{
	struct s_philo **philos;
	bool			 someone_died;
	long			 threads_running;
	long			 nphilos;
	long			 start_time;
	long			 time_to_die;
	long			 time_to_sleep;
	long			 time_to_eat;
	long			 max_nmeals;
	pthread_mutex_t *forks;
	pthread_mutex_t	 read;
	pthread_mutex_t	 write;
	pthread_mutex_t	 eat;
	pthread_mutex_t	 death;
} t_program_data;

typedef struct s_philo
{
	t_program_data	*data;
	unsigned int	 id;
	bool			 is_dead;
	unsigned int	 last_meal_time;
	unsigned int	 nmeals_eaten;
	pthread_t		 thread;
	pthread_mutex_t *r_fork;
	pthread_mutex_t *l_fork;
	pthread_mutex_t	 mutex;
} t_philo;

// check user input
int	 check_input(int argc, char **argv);
long ft_mini_atol(char *str);

// utils
int	 print_error(char *str, int errorcode);
long get_current_time(void);
long time_current(void);
long time_passed(long start_time);
int	 my_usleep(size_t milisec);

// main
void init_program_data(t_program_data *program_data, char **argv);
int	 init_forks(t_program_data *program_data);
int	 init_philos(t_program_data *program_data);
int	 start_philo_threads(t_program_data *data);

// program_stats_checking
bool has_someone_died(t_philo *philo);
bool checker_philos(t_program_data *data);
void loop(t_program_data *data);

// philo_actions
void *philo_actions(void *vphilo);
void  action_eat(t_philo *philo);
void  action_sleep(t_philo *philo);
void  action_think(t_philo *philo);
void  print_action(t_philo *philo, t_actions action);
#endif // PHILOSOPHERS_H
void *ft_monitor(void *vdata);
bool  philo_is_dead(t_program_data *data);
bool  all_philos_are_full(t_program_data *data);
