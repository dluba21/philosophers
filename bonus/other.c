#include "philo.h"

void print_with_sema(char *str, t_philo *philo) //интересно, зависит ли скорость от того передам ли я философа всего большого или номер только
{
	sem_post(philo->vars->print_bin_sem);
	printf("%ld %d %s", get_time_gap_from_start(philo->vars), \
			philo->n + 1, str);
	sem_wait(philo->vars->print_bin_sem);
	
}

long	ft_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

void	ft_sleep(long ms)
{
	long	time;

	time = ft_time();
	usleep(ms * 850);
	while (ft_time() < time + ms)
		usleep(ms * 3);
}

long	get_time_gap_from_start(t_vars *vars)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - \
			(vars->start.tv_sec * 1000 + \
			vars->start.tv_usec / 1000));
}

long	get_time_gap_from_dinner(t_philo philo)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - \
			(philo.last_dinner.tv_sec * 1000 + \
			philo.last_dinner.tv_usec / 1000));
}
