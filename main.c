#include "philo.h"

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

void print_with_mutex(char *str, t_philo *philo)
{
	pthread_mutex_lock(&(philo->vars->print_mutex));
	printf("%ld %d %s", get_time_gap_from_start(philo->vars), philo->n + 1, str);
	pthread_mutex_unlock(&(philo->vars->print_mutex));
}

void *philo_func(void *data) //sega because fork
{
	int	i;
	
	t_philo *philo = (t_philo *)data;

	if (philo->n % 2 != 0)
		ft_sleep(1);
	
	
	while (1)
	{
		pthread_mutex_lock(philo->min_fork);
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
		
		philo->dinner_counter--;
		if (!philo->dinner_counter)
			break;
		print_with_mutex("is sleeping\n", philo);
		
		
		
		ft_sleep(philo->vars->time_to_sleep);

		print_with_mutex("is thinking\n", philo);
	}
//	philo->vars->not_hungry++;
	
	return (NULL);
}


int check_if_died(t_vars *vars)
{
	int	i;
	int	n;

	n = vars->number_of_philosophers;
	while (1)
	{
		i = 0;
		while (i < n)
		{
			pthread_mutex_lock(&(vars->philos[i].dining_mutex));
			if (get_time_gap_from_dinner(vars->philos[i]) > vars->time_to_die)
			{
				print_with_mutex("thread is died\n", vars->philos + i);
				pthread_mutex_unlock(&(vars->philos[i].dining_mutex));
				exit(0);
			}
			pthread_mutex_unlock(&(vars->philos[i].dining_mutex));
			i++;
		}
	}
}



int philos_creator(t_vars *vars) //make threads
{
	int	ret;
	int	i;

	i = 0;
	
	vars->philos = (t_philo *)malloc(sizeof(t_philo) * vars->number_of_philosophers);
	if (!vars->philos)
	{
		printf("thread creating error: can't malloc\n");
		return (1);
	}
	attribute_forks_to_philos(vars->philos, vars);
	gettimeofday(&(vars->start), NULL);
	while (i < vars->number_of_philosophers)
	{
		ret = pthread_create(&(vars->philos[i].id), NULL, philo_func, (void *)&(vars->philos[i]));
		if (ret != 0)
		{
			free(vars->philos);
			printf("thread error: can't init\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 5 && argc != 6) //change with number of dining
	{
		printf("problem with argc\n");
		return (0);
	}
	if (argv_parser(&vars, argc, argv) == 1)
	{
		
	}
	if (mutex_creator(&vars) == 1)
	{
		
	}
	if (philos_creator(&vars) == 1)
	{
		
	}

	if (!check_if_died(&vars))
	{
		free(vars.philos);
		join_all_threads(&vars);
//		pthread_mutex_destroy
		return (0);
	}
	
		

}
