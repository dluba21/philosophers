#include "philo.h"

//void ft_sleep(long ms)
//{
//	t_time a;
//	t_time	start;
//
//	gettimeofday(&start, NULL);
//	ms *= 1000;
//	while (1)
//	{
//		usleep(50); //change to number
//		gettimeofday(&a, NULL);
//		if ((a.tv_sec - start.tv_sec) * 1000000 + (a.tv_usec - start.tv_usec) > ms)
//			break;
//	}
//}
long	ft_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}
void ft_sleep(long ms)
{
	long	time;

	time = ft_time();
	usleep(ms * 920);
	while (ft_time() < time + ms)
		usleep(ms * 4);
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
