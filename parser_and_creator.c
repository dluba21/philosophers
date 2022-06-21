/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_and_creator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:59:30 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/05/29 22:59:30 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	argv_parser(t_vars *vars, int argc, char **argv)
{
	vars->number_of_philosophers = ft_atoi(argv[1]);
	vars->time_to_die = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		vars->dinner_number = ft_atoi(argv[5]);
	else
		vars->dinner_number = 0;
	if (vars->number_of_philosophers < 0 || vars->time_to_die < 0 \
		|| vars->time_to_eat < 0 || vars->time_to_sleep < 0 || \
		vars->dinner_number < 0)
		return (1);
	vars->not_hungry_yet = 0;
	return (0);
}

int	mutex_creator(t_vars *vars)
{
	int	i;
	int	n;

	i = 0;
	n = vars->number_of_philosophers;
	pthread_mutex_init(&vars->print_mutex, NULL);
	pthread_mutex_init(&vars->dining_number_mutex, NULL);
	vars->forks = (t_mutex *)malloc(sizeof(t_mutex) * n);
	if (!vars->forks)
	{
		printf("mutex error: can't malloc\n");
		return (1);
	}
	while (i < vars->number_of_philosophers)
	{
		if (pthread_mutex_init(&vars->forks[i++], NULL) != 0)
		{
			printf("mutex error: can't init\n");
			free(vars->forks);
			return (1);
		}
	}
	return (0);
}

void	attribute_forks_to_philos(t_philo *philos, t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->number_of_philosophers)
	{
		philos[i].n = i;
		philos[i].vars = vars;
		pthread_mutex_init(&(philos[i].dining_mutex), NULL);
		philos[i].min_fork = &(vars->forks[i]);
		philos[i].fork_min = i + 1;
		philos[i].dinner_counter = vars->dinner_number;
		if (i != vars->number_of_philosophers - 1)
			philos[i].max_fork = &(vars->forks[i + 1]);
		else
			philos[i].max_fork = &(vars->forks[0]);
		gettimeofday(&(philos[i].last_dinner), NULL);
		i++;
	}
}

void	mutex_and_philos_destroyer(t_vars *vars)
{
	int	i;

	i = 0;
//	while (i < vars->number_of_philosophers)
//	{
//		pthread_mutex_unlock(&(vars->forks[i]));
//		if (pthread_mutex_destroy(&(vars->forks[i++])))
//			printf("destroy mutex error\n");
//	}
//	pthread_mutex_unlock(&vars->print_mutex);
//	pthread_mutex_unlock(&vars->dining_number_mutex);
//	pthread_mutex_destroy(&vars->print_mutex);
//	pthread_mutex_destroy(&vars->dining_number_mutex);
	free(vars->forks);
	free(vars->philos);
}
