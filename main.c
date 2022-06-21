/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:59:27 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/05/29 22:59:27 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_period(t_philo *philo)
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
}

void	*philo_func(void *data)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->n % 2 != 0)
		ft_sleep(1);
	while (1)
	{
		eating_period(philo);
		if (!(--philo->dinner_counter))
		{
			pthread_mutex_lock(&(philo->vars->dining_number_mutex));
			++philo->vars->not_hungry_yet;
			pthread_mutex_unlock(&(philo->vars->dining_number_mutex));
			break ;
		}
		print_with_mutex("is sleeping\n", philo);
		ft_sleep(philo->vars->time_to_sleep);
		print_with_mutex("is thinking\n", philo);
	}
	return (NULL);
}

int	check_if_died(t_vars *vars)
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
			if (vars->not_hungry_yet == vars->number_of_philosophers)
				return (1);
			if (get_time_gap_from_dinner(vars->philos[i]) > vars->time_to_die)
			{
				print_with_mutex("thread is died\n", vars->philos + i);
				pthread_mutex_unlock(&(vars->philos[i].dining_mutex));
				return (1);
			}
			pthread_mutex_unlock(&(vars->philos[i].dining_mutex));
			i++;
		}
	}
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 5 && argc != 6)
	{
		printf("problem with argc\n");
		return (0);
	}
	if (argv_parser(&vars, argc, argv))
		return (0);
	if (mutex_creator(&vars))
		return (0);
	if (philos_creator(&vars))
	{
		mutex_and_philos_destroyer(&vars);
		return (0);
	}
	if (check_if_died(&vars))
	{
		mutex_and_philos_destroyer(&vars);
		return (0);
	}
}
