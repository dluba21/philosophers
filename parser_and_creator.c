#include "philo.h"

void argv_parser(t_vars *vars, int argc, char **argv)
{

	vars->number_of_philosophers = ft_atoi(argv[1]); //in milisec!!!
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
}

void	mutex_creator(t_vars *vars)
{
	int	i;
	int	ret;

	i = 0;
	pthread_mutex_init(&vars->print_mutex, NULL);
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

void attribute_forks_to_philos(t_philo *philos, t_vars *vars) //mb not left and right fork, mb max_fork, min_fork
{
	int	i;

	i = 0;
	while (i < vars->number_of_philosophers)
	{
		philos[i].n = i;
		philos[i].vars = vars;
		pthread_mutex_init(&(philos[i].dining_mutex), NULL);
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
		gettimeofday(&(philos[i].last_dinner), NULL);
		i++;
	}
}
