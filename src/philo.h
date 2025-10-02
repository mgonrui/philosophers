/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariogo2 <mariogo2@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:49:22 by mariogo2          #+#    #+#             */
/*   Updated: 2025/10/02 23:51:23 by mariogo2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_NPHILOS 200
# define TIME_TO_THINK 2

typedef enum e_actions
{
	GRAB_FORK,
	EAT,
	THINK,
	SLEEP,
	DIE,
}					t_actions;

typedef struct s_data
{
	struct s_philo	**philos;
	bool			end_program;
	long			nphilos;
	long			start_time;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	long			max_nmeals;
	pthread_mutex_t	*forks;
	pthread_mutex_t	eat;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_end;
}					t_data;

typedef struct s_philo
{
	t_data			*data;
	unsigned int	id;
	long			last_meal_time;
	unsigned int	nmeals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	mutex;
}					t_philo;

// check user input
int					check_input(int argc, char **argv);
long				mini_atol(char *str);

// utils
int					print_error(char *str, int errorcode);
long				time_current(void);
long				time_passed(long start_time);
int					my_usleep(long milisec);

// main
int					init_program_data(t_data *program_data, char **argv);
int					init_forks(t_data *program_data);
int					init_philos(t_data *program_data);
int					start_philo_threads(t_data *data);

// program_stats_checking
bool				has_someone_died(t_philo *philo);
void				cleanup(t_data *data);

// philo_actions
void				*philo_actions(void *vphilo);
void				action_eat(t_philo *philo);
void				action_die(t_philo *philo);
void				action_sleep(t_philo *philo);
void				action_think(t_philo *philo);
int					print_action(t_philo *philo, t_actions action);
void				*arbiter(void *vdata);
bool				philo_is_dead(t_data *data);
bool				all_philos_are_full(t_data *data);
#endif // PHILOSOPHERS_H
