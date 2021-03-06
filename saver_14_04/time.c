#include "philo.h"

void ft_sleep(long ms)
{
	t_time a;
	t_time	start;

	gettimeofday(&start, NULL);
	ms *= 1000;
//	start = a.tv_sec * 1000 + a.tv_usec / 1000;
	while (1)
	{
		usleep(1);
		gettimeofday(&a, NULL);
		if ((a.tv_sec - start.tv_sec) * 1000000 + (a.tv_usec - start.tv_usec) > ms)
			break;
	}
}

long get_time_gap_from_start(t_vars *vars)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - \
			(vars->start.tv_sec * 1000 + vars->start.tv_usec / 1000));
}

long get_time_gap_from_dinner(t_philo philo)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - \
			(philo.last_dinner.tv_sec * 1000 + philo.last_dinner.tv_usec / 1000));
}
