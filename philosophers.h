#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <limits.h>
#include <unistd.h>

#define MAX_NPHILOS 200

typedef struct s_fork
{
	int id;
	pthread_mutex_t mutex;
} t_fork;

typedef struct s_philosopher
{
	int id_philosopher;
	pthread_t id_thread;
	t_fork *r_fork;
	t_fork *l_fork;
	bool isdead;
	unsigned int last_meal_time;
	unsigned int nmeals_eated;
} t_philosopher;

void ft_check_input(int argc, char **argv);

#endif // PHILOSOPHERS_H
