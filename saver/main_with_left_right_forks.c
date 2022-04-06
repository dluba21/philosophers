#include "philo.h"

void argv_parser(t_vars *vars, int argc, char **argv)
{

	vars->number_of_philosophers = ft_atoi(argv[1]) * 1000; //in milisec!!!
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

//int pthread_create(pthread_t *restrict thread,
//const pthread_attr_t *restrict attr,
//void *(*start_routine)(void *),
//void *restrict arg);

void	find_min_max_forks(t_vars *vars)
{
	int	i
	
	i = 0;
	if ()
}

//void	*philo_func(void *data)
//{
//	t_mutex	max_fork;
//	t_mutex	min_fork;
	
	
	while (1)
	{
		usleep(10000);
		printf("aboba\n");
	}
}

void attribute_forks_to_philos(t_philo *philos, t_vars *vars) //mb not left and right fork, mb max_fork, min_fork
{
	int	i;

	i = 0;
	while (i < vars->number_of_philosophers)
	{
		if (i == 0)
			philos[i].left_fork = &(vars->forks[vars->number_of_philosophers - 1]);
		else
			philos[i].left_fork = &(vars->forks[i - 1]);
		philos[i].right_fork = &(vars->forks[i]);
		i++;
	}
}

void philos_creator(t_vars *vars) //make threads
{
	int	i;

	i = 0;
	vars->philos = (t_philo *)malloc(sizeof(t_philo) * vars->number_of_philosophers);
	if (!vars->philos)
	{
		printf("thread creating error: can't malloc\n");
		return ; //make system like exit
	}
	attribute_forks_to_philos(vars->philos, vars);
	while (i < vars->number_of_philosophers)
	{
		if (pthread_create(&(vars->philos[i++].id), NULL, philo_func, NULL) != 0)
		{
			printf("mutex error: can't init\n");
			return ;
		}
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

