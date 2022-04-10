#include "philo.h"

void argv_parser(t_vars *vars, int argc, char **argv)
{

	vars->number_of_philosophers = ft_atoi(argv[1]); //in milisec!!!
	vars->time_to_die = ft_atoi(argv[2]) * 1000;
	vars->time_to_eat = ft_atoi(argv[3]) * 1000;
	vars->time_to_sleep = ft_atoi(argv[4]) * 1000;
}

void ft_sleep(long ms)
{
	t_time a;
	long	start;

	gettimeofday(&a, NULL);
	start = a.tv_sec * 1000000 + a.tv_usec;
	while (1)
	{
		gettimeofday(&a, NULL);
		if (a.tv_sec * 1000000 + a.tv_usec - start > 1000 * ms)
			break;
	}
}

long get_time_gap_from_start(t_vars *vars)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - \
			(vars->start.tv_sec * 1000 - vars->start.tv_usec / 1000));
}

long get_time_gap_from_dinner(t_philo philo)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - \
			(philo.last_dinner.tv_sec * 1000 - philo.last_dinner.tv_usec / 1000));
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


void	join_all_threads(t_vars *vars)
{
	int	i;
	int	ret;

	i = 0;
	while (i < vars->number_of_philosophers)
	{
		ret = pthread_join(vars->philos[i].id, NULL);
		if (ret != 0)
			printf("\ncan't join :(\n");
		i++;
	}
}

void *philo_func(void *data) //sega because fork
{
	int	i;
	
	
	

//	someArgs_t *arg = (someArgs_t*) args;
	t_philo *philo = (t_philo *)data;
//		i = vars->counter;

//	if (i % 2 != 0)
//		usleep(2000);
	while (1)
	{
		
		pthread_mutex_lock(philo->min_fork);
		printf("{%ld} [%d] has taken a fork_1\n", get_time_gap_from_start(philo->vars), philo->n + 1);
		pthread_mutex_lock(philo->max_fork);
		printf("{%ld} [%d] has taken a fork_2\n", get_time_gap_from_start(philo->vars), philo->n + 1);
		printf("{%ld} [%d] is eating\n", get_time_gap_from_start(philo->vars), philo->n + 1);
		ft_sleep(philo->vars->time_to_eat / 1000);
		gettimeofday(&(philo->last_dinner), NULL);
		philo->dinner_counter++;
//		printf("\n{%d}  [%d]\n", philo->n + 1, philo->dinner_counter);
		pthread_mutex_unlock(philo->max_fork);
		pthread_mutex_unlock(philo->min_fork);
//		gettimeofday(philo->last_dinner);
		
		printf("{%ld} [%d] is sleeping\n", get_time_gap_from_start(philo->vars), philo->n + 1);
		ft_sleep(philo->vars->time_to_sleep / 1000);
		printf("{%ld} [%d] is thinking\n", get_time_gap_from_start(philo->vars), philo->n + 1);

	}
//	sleep(10);
	return (NULL);
}

//		vars->philos[i].numb = i;
//		vars->philos[i].vars = vars; //snachala initializirovat philos, prosvoit nomera i *vars,

void check_if_died(t_vars *vars)
{
	int	i;
	int	n;
//	t_time	dinner;
//	t_time	now;

	n = vars->number_of_philosophers;
//	printf("\n\n\n%d\n\n\n", vars->time_to_die);
	while (1)
	{
		i = 0;
		while (i < n)
		{
			if (vars->philos[i].dinner_counter > 0 \
					&& get_time_gap_from_dinner(vars->philos[i]) > vars->time_to_die / 1000)
			{
				printf("\n\n\n{%ld} [%d] thread is died!!!!\n\n\n", get_time_gap_from_start(vars), i + 1);
//				join_all_threads(vars);
				exit(0);
			}
			else if (get_time_gap_from_start(vars) > vars->time_to_die / 1000 && \
					 vars->philos[i].dinner_counter == 0)
			{
//				printf("gap = %ld, die = %d\n", get_time_gap_from_start(vars), vars->time_to_die / 1000);
				printf("\n\n\n{%ld} [%d] thread is died non eating!!!!\n\n\n", get_time_gap_from_start(vars), i + 1);
//				join_all_threads(vars);
				exit(0);
			}
			i++;
		}
	}
}

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
	gettimeofday(&(vars->start), NULL);
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
	
	check_if_died(&vars);
	sleep(1000);

}



//int pthread_create(*ptherad_t, const pthread_attr_t *attr, void* (*start_routine)(void*), void *arg)

