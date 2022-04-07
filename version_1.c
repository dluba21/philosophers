#include "philo.h"

void argv_parser(t_vars *vars, int argc, char **argv)
{

	vars->number_of_philosophers = ft_atoi(argv[1]); //in milisec!!!
	vars->time_to_die = ft_atoi(argv[2]) * 1000;
	vars->time_to_eat = ft_atoi(argv[3]) * 1000;
	vars->time_to_sleep = ft_atoi(argv[4]) * 1000;
}

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
	t_philo *philo;
	

//	someArgs_t *arg = (someArgs_t*) args;
	t_vars *vars = (t_vars *)data;
//		i = vars->counter;
	philo = &(vars->philos[]);

	if (i % 2 == 0)
		usleep(2000);
	while (1)
	{
		pthread_mutex_lock(philo->min_fork);
		printf("[%d] has taken a fork_1\n", i);
		pthread_mutex_lock(philo->max_fork);
		printf("[%d] has taken a fork_2\n", i);
		printf("[%d] is eating\n", i);
		usleep(vars->time_to_eat);
		pthread_mutex_unlock(philo->max_fork);
		pthread_mutex_unlock(philo->min_fork);
		printf("[%d] is sleeping\n", i);
		usleep(vars->time_to_sleep);
		printf("[%d] is thinking\n", i);

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

//	i = 0;
	vars->counter = 0;
	vars->philos = (t_philo *)malloc(sizeof(t_philo) * vars->number_of_philosophers);
	if (!vars->philos)
	{
		printf("thread creating error: can't malloc\n");
		return ; //make system like exit
	}
	attribute_forks_to_philos(vars->philos, vars);
//	printf("{%d}\n", vars->number_of_philosophers);
	while (vars->counter < vars->number_of_philosophers)
	{
		ret = pthread_create(&(vars->philos[vars->counter].id), NULL, philo_func, (void *)vars);
		if (ret != 0)
		{
			printf("thread error: can't init\n");
			return ;
		}
//		printf("{%d}\n", vars->counter);
		vars->counter++;
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

