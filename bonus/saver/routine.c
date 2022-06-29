#include "philo.h"



void	eating_period(t_philo *philo)
{
//	sem_post(philo->vars->death_bin_sem);  //semaphore na smert'
	
	sem_wait(philo->vars->forks_sem);
	print_with_sema("has taken a fork\n", philo);
	sem_wait(philo->vars->forks_sem);
	print_with_sema("has taken a fork\n", philo);
//	sem_post(philo->vars->first_dinner_sem);
//	pthread_mutex_lock(&(philo->dining_mutex));
	gettimeofday(&(philo->last_dinner), NULL);
//	pthread_mutex_unlock(&(philo->dining_mutex));
	print_with_sema("is eating\n", philo);
	ft_sleep(philo->vars->time_to_eat);
	sem_post(philo->vars->forks_sem);
	sem_post(philo->vars->forks_sem);
	
	
}

void	*routine_philo_func(t_philo *philo)
{
	int		i;

	if ((philo->n + 1) % 2 == 0) // четные задерживаются
//		usleep(1000 * (philo->vars->time_to_die * 0.5));
		usleep(1000);
	
	while (1)
	{
		
		eating_period(philo);
		if (!(--philo->dinner_counter))
		{
			free(philo->vars->pid_array);
			free(philo);
			exit (0);
		}
		print_with_sema("is sleeping\n", philo);
		ft_sleep(philo->vars->time_to_sleep);
		print_with_sema("is thinking\n", philo);
		
//		sem_wait(philo->vars->death_bin_sem);
	}
	return (NULL);
}



void	*checker_thread_func(void *data)
{
	int		i;
	int		n;
	t_checker *checker_thread;

	checker_thread = (t_checker *)data;
	n = checker_thread->vars->number_of_philosophers;

	ft_sleep(500);
	while (1)
	{
		i = 0;
		while (i < n)
		{
			ft_sleep(1);
			if (get_time_gap_from_dinner(*checker_thread->philo) > checker_thread->vars->time_to_die)
			{
				sem_wait(checker_thread->vars->death_bin_sem);
				print_with_sema("thread is died\n\n\n\n\n", checker_thread->philo);
				free(checker_thread->vars->pid_array);
				free(checker_thread->philo);
//				sleep(1000);
				exit (1);
	
				
			}
			i++;
		}
	}
}

//int	check_if_died(t_vars *vars)
//{
//	int	i;
//	int	n;
//
//	n = vars->number_of_philosophers;
//	while (1)
//	{
//		i = 0;
//		while (i < n)
//		{
//			pthread_mutex_lock(&(vars->philos[i].dining_mutex));
//			if (vars->not_hungry_yet == vars->number_of_philosophers)
//				return (1);
//			if (get_time_gap_from_dinner(vars->philos[i]) > vars->time_to_die)
//			{
//				print_with_sema("thread is died\n", vars->philos + i);
//				pthread_mutex_unlock(&(vars->philos[i].dining_mutex));
//				return (1);
//			}
//			pthread_mutex_unlock(&(vars->philos[i].dining_mutex));
//			i++;
//		}
//	}
//}
