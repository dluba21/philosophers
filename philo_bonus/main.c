/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:59:27 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/07/01 03:00:33 by dluba            ###   ########.fr       */
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
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars		vars;

	if (argc != 5 && argc != 6)
	{
		printf("problem with argc\n");
		return (0);
	}
	if (argv_parser(&vars, argc, argv))
		return (0);
	if (semas_creator(&vars))
		return (0);
	if (process_philos_creator(&vars))
	{
		printf("process_philos_creator error\n");
		return (0);
	}
}
