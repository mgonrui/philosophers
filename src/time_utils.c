#include "philo.h"
#include <sys/time.h>

long time_current(void)
{
	struct timeval time;

	if (gettimeofday(&time, NULL) == -1)
		print_error("gettimeofday function error\n", 3);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int my_usleep(size_t milisec)
{
	size_t start;

	start = time_current();
	while ((time_current() - start) < milisec)
		usleep(1);
	return (0);
}

long time_passed(long start_time)
{
	long time_passed;
	time_passed = time_current() - start_time;
	return time_passed;
}
