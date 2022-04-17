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

void *philo_func(void *data) //sega because fork
{
	int	i;
	
	
	

//	someArgs_t *arg = (someArgs_t*) args;
	t_philo *philo = (t_philo *)data;
//		i = vars->counter;
//	printf("ok\n");
//	gettimeofday(&(philo->last_dinner), NULL);
	if (philo->n % 2 != 0)
		ft_sleep(1);
	
	
	while (1)
	{
		pthread_mutex_lock(philo->min_fork);
		
		///////////////-------------------->>>>>>>>>>>
//		pthread_mutex_lock(&(philo->vars->print_mutex));
//		printf("{%ld}\t{%ld}\t[%d] has taken a fork_1\t\t(%d)\n", get_time_gap_from_start(philo->vars), get_time_gap_from_dinner(*philo),  philo->n + 1, philo->fork_min);
//		pthread_mutex_unlock(&(philo->vars->print_mutex));
		///////////////<<<<<<<<<<<<<<<<<----------------------------
		pthread_mutex_lock(&(philo->vars->print_mutex));
		printf("%ld %d has taken a fork\n", get_time_gap_from_start(philo->vars), philo->n + 1);
		pthread_mutex_unlock(&(philo->vars->print_mutex));
		
		
		pthread_mutex_lock(philo->max_fork);
		
		///////////////-------------------->>>>>>>>>>>
//		pthread_mutex_lock(&(philo->vars->print_mutex));
//		printf("{%ld}\t{%ld}\t[%d] has taken a fork_2\t\t(%d)\n", get_time_gap_from_start(philo->vars), get_time_gap_from_dinner(*philo), philo->n + 1, philo->fork_max);
//		pthread_mutex_unlock(&(philo->vars->print_mutex));
		///////////////<<<<<<<<<<<<<<<<<----------------------------
		pthread_mutex_lock(&(philo->vars->print_mutex));
		printf("%ld %d has taken a fork\n", get_time_gap_from_start(philo->vars), philo->n + 1);
		pthread_mutex_unlock(&(philo->vars->print_mutex));
		
		
		pthread_mutex_lock(&(philo->dining_mutex));
			gettimeofday(&(philo->last_dinner), NULL);
			philo->dinner_counter++;
			pthread_mutex_unlock(&(philo->dining_mutex));
		
		///////////////-------------------->>>>>>>>>>>
//		pthread_mutex_lock(&(philo->vars->print_mutex));
//		printf("{%ld}\t{%ld}\t[%d] is eating\n", get_time_gap_from_start(philo->vars), get_time_gap_from_dinner(*philo), philo->n + 1);
//		pthread_mutex_unlock(&(philo->vars->print_mutex));
		///////////////<<<<<<<<<<<<<<<<<----------------------------
		pthread_mutex_lock(&(philo->vars->print_mutex));
		printf("%ld %d is eating\n", get_time_gap_from_start(philo->vars), philo->n + 1);
		pthread_mutex_unlock(&(philo->vars->print_mutex));
		
		
		ft_sleep(philo->vars->time_to_eat);
		
//		usleep(philo->vars->time_to_eat * 1000);
		
	
//		printf("\n{%d}  [%d]\n", philo->n + 1, philo->dinner_counter);
		pthread_mutex_unlock(philo->max_fork);
//		pthread_mutex_lock(&(philo->vars->print_mutex));
//		printf("{%ld}\t{%ld}\t[%d] put a fork_2\t\t(%d)\n", get_time_gap_from_start(philo->vars), get_time_gap_from_dinner(*philo), philo->n + 1, philo->fork_max);
//		pthread_mutex_unlock(&(philo->vars->print_mutex));
		pthread_mutex_unlock(philo->min_fork);
		
//		pthread_mutex_lock(&(philo->vars->print_mutex));
//		printf("{%ld}\t{%ld}\t[%d] put a fork_1\t\t(%d)\n", get_time_gap_from_start(philo->vars), get_time_gap_from_dinner(*philo), philo->n + 1, philo->fork_min);
//		pthread_mutex_unlock(&(philo->vars->print_mutex));
//		gettimeofday(philo->last_dinner);
		
//		///////////////-------------------->>>>>>>>>>>
//		pthread_mutex_lock(&(philo->vars->print_mutex));
//		printf("{%ld}\t{%ld}\t[%d] is sleeping\n", get_time_gap_from_start(philo->vars), get_time_gap_from_dinner(*philo), philo->n + 1);
//		pthread_mutex_unlock(&(philo->vars->print_mutex));
//		///////////////<<<<<<<<<<<<<<<<<----------------------------
		pthread_mutex_lock(&(philo->vars->print_mutex));
		printf("%ld %d is sleeping\n", get_time_gap_from_start(philo->vars), philo->n + 1);
		pthread_mutex_unlock(&(philo->vars->print_mutex));
		
		
		
		ft_sleep(philo->vars->time_to_sleep);
//		usleep(philo->vars->time_to_sleep * 1000);
		
//		///////////////-------------------->>>>>>>>>>>
//		pthread_mutex_lock(&(philo->vars->print_mutex));
//		printf("{%ld}\t{%ld}\t[%d] is thinking\n", get_time_gap_from_start(philo->vars), get_time_gap_from_dinner(*philo), philo->n + 1);
//		pthread_mutex_unlock(&(philo->vars->print_mutex));
//		///////////////<<<<<<<<<<<<<<<<<----------------------------
		pthread_mutex_lock(&(philo->vars->print_mutex));
		printf("%ld %d is thinking\n", get_time_gap_from_start(philo->vars), philo->n + 1);
		pthread_mutex_unlock(&(philo->vars->print_mutex));

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
			pthread_mutex_lock(&(vars->philos[i].dining_mutex));
			if (get_time_gap_from_dinner(vars->philos[i]) > vars->time_to_die)
			{
				pthread_mutex_lock(&(vars->print_mutex));
				printf("\n\n\n\n\n\n\n\n\ntime_from_last_dinner: {%ld}\n", get_time_gap_from_dinner(vars->philos[i]));
				printf("{%ld} [%d] thread is died!!!!\n\n\n\n\n\n\n", get_time_gap_from_start(vars), i + 1);
				pthread_mutex_unlock(&(vars->print_mutex));
//				join_all_threads(vars);
//				_exit(0);
//				ft_sleep(10);
			}
			pthread_mutex_unlock(&(vars->philos[i].dining_mutex));
			i++;
		}
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
//	printf("getpid = %d\n\n\n", getpid());
	
	if (argc != 5) //change with number of dining
	{
		printf("problem with argc\n");
		return (0);
	}
	argv_parser(&vars, argc, argv);
	mutex_creator(&vars);

	philos_creator(&vars);
	
	ft_sleep(vars.time_to_die);
	check_if_died(&vars);
	sleep(1000);

}



//int pthread_create(*ptherad_t, const pthread_attr_t *attr, void* (*start_routine)(void*), void *arg)

