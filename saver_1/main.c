#include "philo.h"

void argv_parser(t_vars *vars, int argc, char **argv)
{

	vars->number_of_philosophers = ft_atoi(argv[1]); //in milisec!!!
	vars->time_to_die = ft_atoi(argv[2]) * 1000;
	vars->time_to_eat = ft_atoi(argv[3]) * 1000;
	vars->time_to_sleep = ft_atoi(argv[4]) * 1000;
}

//void	is_died(t_philo *philo)
//{
//	t_time *temp;
//	long	new_time;
//	long	old_time;
//
//	gettimeofday(temp, NULL);
//	old_time = philo->last_dinner->tv_sec * 1000000 + philo->last_dinner->tv_usec;
//	new_time = temp->tv_sec * 1000000 + temp->tv_usec;
//	if (new_time - old_time >= philo->vars->time_to_die)
//	{
//		printf("\n[%d] is died\n", philo->n);
//	}
//}

void	mutex_creator(t_vars *vars)
{
	int	i;
	int	ret;

	i = 0;
	vars->forks = (t_mutex *)malloc(sizeof(t_mutex) * vars->number_of_philosophers);
	if (!vars->forks)
	{
		printf("mutex error: can't malloc\n");
		return ; //make system like exit
	}
	while (i < vars->number_of_philosophers)
	{

		if (pthread_mutex_init(&vars->forks[i++], NULL) != 0)
		{
			printf("mutex error: can't init\n");
			return ;
		}
	}
	
//	for (int j = 0; i < vars->number_of_philosophers; i++)
//	{
//		printf("%p ", vars->forks[j]);
//	}
}


void *philo_func(void *data) //sega because fork
{
	int	i;
	
	

//	someArgs_t *arg = (someArgs_t*) args;
	t_philo *philo = (t_philo *)data;
//		i = vars->counter;

//	if (i % 2 == 0)
//		usleep(2000);
	while (1)
	{
		pthread_mutex_lock(philo->min_fork);
		printf("[%d] has taken a fork_1\n", philo->n);
		pthread_mutex_lock(philo->max_fork);
		printf("[%d] has taken a fork_2\n", philo->n);
		printf("[%d] is eating\n", philo->n);
		usleep(philo->vars->time_to_eat);
		pthread_mutex_unlock(philo->max_fork);
		pthread_mutex_unlock(philo->min_fork);
//		gettimeofday(philo->last_dinner);
//		philo->dinner_counter++;
//		is_died(philo);
		printf("[%d] is sleeping\n", philo->n);
		usleep(philo->vars->time_to_sleep);
		printf("[%d] is thinking\n", philo->n);

	}
//	sleep(10);
	return (NULL);
}

//		vars->philos[i].numb = i;
//		vars->philos[i].vars = vars; //snachala initializirovat philos, prosvoit nomera i *vars,

void attribute_forks_to_philos(t_philo *philos, t_vars *vars) //mb not left and right fork, mb max_fork, min_fork
{
	int	i;

	i = 0;
	while (i < vars->number_of_philosophers)
	{
		philos[i].n = i;
		philos[i].vars = vars;
		if (i == 0)
		{
			philos[i].min_fork = &(vars->forks[i]); //right fork
			philos[i].max_fork = &(vars->forks[vars->number_of_philosophers - 1]); //left fork
		}
		else
		{
			philos[i].min_fork = &(vars->forks[i - 1]); //left fork
			philos[i].max_fork = &(vars->forks[i]); //right fork
		}
		i++;
	}
}

void philos_creator(t_vars *vars) //make threads
{
	int	ret;
	int	i;

	i = 0;
	vars->philos = (t_philo *)malloc(sizeof(t_philo) * vars->number_of_philosophers);
	if (!vars->philos)
	{
		printf("thread creating error: can't malloc\n");
		return ; //make system like exit
	}
	attribute_forks_to_philos(vars->philos, vars);
//	printf("{%d}\n", vars->number_of_philosophers);
	while (i < vars->number_of_philosophers)
	{
		ret = pthread_create(&(vars->philos[i].id), NULL, philo_func, (void *)&(vars->philos[i]));
		if (ret != 0)
		{
			printf("thread error: can't init\n");
			return ;
		}
//		printf("{%d}\n", vars->counter);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_vars	vars;
	
	if (argc != 5) //change with number of dining
	{
		printf("problem with argc\n");
		return (0);
	}
	argv_parser(&vars, argc, argv);
	mutex_creator(&vars);
	philos_creator(&vars);
	
	sleep(1000);

}



//int pthread_create(*ptherad_t, const pthread_attr_t *attr, void* (*start_routine)(void*), void *arg)

