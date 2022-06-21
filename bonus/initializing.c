/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:59:23 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/05/29 22:59:25 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	semas_creator(t_vars *vars)
{
	
//	sem_t	*dinner_numb_sem; //lishniy ne nado peredelivat bilo
//	t_time	start; //before fork
//	t_mutex	*forks; //
//	t_philo	*philos;
////	t_mutex	print_mutex; //semaphore n = 1
//	sem_t	*print_bin_sem;
////	t_mutex	dining_number_mutex; //semaphore n = 1
//	sem_t	*dining_numb_bin_sem;
////	int		not_hungry_yet; //semaphore n = 0
//	sem_t	*death_bin_sem;
	
	vars->forks_sem = sem_open("/sem_1", O_CREAT | O_EXCEL, 0666, vars->number_of_philosophers);
	vars->print_bin_sem = sem_open("/sem_2", O_CREAT | O_EXCEL, 0666, 1);
	vars->dining_numb_bin_sem = sem_open("/sem_3", O_CREAT | O_EXCEL, 0666, 1);
	vars->death_bin_sem = sem_open("/sem_4", O_CREAT | O_EXCEL, 0666, 1);
	
}


int	philos_creator(t_vars *vars)
{
	int	i;
	int	pid;

	i = 0;
	while (i < vars->number_of_philosophers)
	{
		pid = fork();
		if (pid == 0)
		{
			philo_func;
			break;
		}
		
	}
}


int	philos_and_semas_init(t_vars *vars)
{

	if (semas_creator(t_vars *vars))
		
	if (philos_creator())
		
	if (attribute_semas_to_philos)
		
	
	
}







void	print_with_mutex(char *str, t_philo *philo)
{
	pthread_mutex_lock(&(philo->vars->print_mutex));
	printf("%ld %d %s", get_time_gap_from_start(philo->vars), \
			philo->n + 1, str);
	pthread_mutex_unlock(&(philo->vars->print_mutex));
}

int	philos_init(t_vars *vars)
{
	vars->philos = (t_philo *)malloc(sizeof(t_philo) * \
					vars->number_of_philosophers);
	if (!vars->philos)
	{
		printf("thread creating error: can't malloc\n");
		return (1);
	}
	attribute_forks_to_philos(vars->philos, vars);
	return (0);
}

int	philos_creator(t_vars *vars)
{
	int	ret_1;
	int	ret_2;
	int	i;

	i = 0;
	if (philos_init(vars))
		return (1);
	gettimeofday(&(vars->start), NULL);
	while (i < vars->number_of_philosophers)
	{
		ret_1 = pthread_create(&(vars->philos[i].id), NULL, philo_func, \
				(void *)&(vars->philos[i]));
		ret_2 = pthread_detach(vars->philos[i].id);
		if (ret_1 || ret_2)
		{
			free(vars->philos);
			printf("thread error\n");
			return (1);
		}
		i++;
	}
	return (0);
}
