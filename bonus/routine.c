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

	//dalee ya ne uchitvayu zaderzhku philos chetnih
//	printf("n = %d\n", philo->n);
//	printf("philo %d here\n", philo->n);
//	printf("philo  here\n");
//	printf("aboba\n");
	if ((philo->n + 1) % 2 == 0) // четные задерживаются
//		usleep(1000 * (philo->vars->time_to_die * 0.5));
		usleep(1000);
	
	while (1)
	{
		
		eating_period(philo);
		if (!(--philo->dinner_counter))
		{
//			printf("[%d] not hungry!!!!\n\n\n", philo->n);
//			sem_post(philo->vars->death_bin_sem);
//			free(data); //mb ne uspeet doyti i utechka
			exit (0);
		}

//		{
//			++philo->vars->not_hungry_yet; //zachitit' semaphorom bin_dining_number_sema
//			sem_wait(dining_number_sema);
//			exit (0);
//		}
		
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
//	sleep(2); //check na rabotu boobshe
//	ft_sleep(1500);
//	sem_wait(checker_thread->vars->first_dinner_sem);
//	printf("checker has started\n");
	ft_sleep(500);
	while (1)
	{
		i = 0;
		while (i < n)
		{
//			pthread_mutex_lock(&(vars->philos[i].dining_mutex));
			ft_sleep(1);
//			if (vars->not_hungry_yet == vars->number_of_philosophers)
//			{
//
//				exit (0);
//			}
			if (get_time_gap_from_dinner(*checker_thread->philo) > checker_thread->vars->time_to_die)
			{
//				printf("\n\n\n\n\ngap = %lu\n", get_time_gap_from_dinner(*checker_thread->philo));
//				printf("time_to_die = %d\n", checker_thread->vars->time_to_die);
				sem_wait(checker_thread->vars->death_bin_sem);
				print_with_sema("thread is died\n\n\n\n\n", checker_thread->philo);
//				exit (1);
				printf("aboba[%d] died pid = %d\n", checker_thread->philo->n, getpid());
//				sleep(1000);
				exit (1);
				
//				sleep(10000);
				
			}
//			pthread_mutex_unlock(&(vars->philos[i].dining_mutex));
			i++;
		}
	}
	printf("outside of checker cycle\n");
//	sleep(10000); //чтобы не выходил чекер случайно хз вдруг
//	exit (0);
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
