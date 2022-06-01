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
