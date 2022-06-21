#include "philo.h"


void	eating_period(t_philo *philo)
{
	sem_post(philo->vars->)
	print_with_mutex("has taken a fork\n", philo);
	pthread_mutex_lock(philo->max_fork);
	print_with_mutex("has taken a fork\n", philo);
	pthread_mutex_lock(&(philo->dining_mutex));
	gettimeofday(&(philo->last_dinner), NULL);
	pthread_mutex_unlock(&(philo->dining_mutex));
	print_with_mutex("is eating\n", philo);
	ft_sleep(philo->vars->time_to_eat);
	pthread_mutex_unlock(philo->min_fork);
	pthread_mutex_unlock(philo->max_fork);
}

void	*routine_thread_func(void *data)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)data; //dalee ya ne uchitvayu zaderzhku philos chetnih
	while (1)
	{
		eating_period(philo);
		if (!(--philo->dinner_counter))
		{
			++philo->vars->not_hungry_yet; //zachitit' semaphorom bin_dining_number_sema
			break ;
		}
		print_with_mutex("is sleeping\n", philo);
		ft_sleep(philo->vars->time_to_sleep);
		print_with_mutex("is thinking\n", philo);
	}
	return (NULL);
}

//void	*philo_func(void *data)
//{
//	int		i;
//	t_philo	*philo;
//
////	philo = (t_philo *)data;
////	if (philo->n % 2 != 0)
////		ft_sleep(1);
//	while (1)
//	{
//		eating_period(philo);
//		if (!(--philo->dinner_counter))
//		{
//			pthread_mutex_lock(&(philo->vars->dining_number_mutex));
//			++philo->vars->not_hungry_yet;
//			pthread_mutex_unlock(&(philo->vars->dining_number_mutex));
//			break ;
//		}
//		print_with_mutex("is sleeping\n", philo);
//		ft_sleep(philo->vars->time_to_sleep);
//		print_with_mutex("is thinking\n", philo);
//	}
//	return (NULL);
//}
