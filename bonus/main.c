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
	
	
	if (philos_and_semas_init(&vars))
		return (0);
	if (philos_creator(&vars))	
	{
		free(vars.philos);
		return (0);
	}
	if (check_if_died(&vars))
	{
		free(vars.philos);
		return (0);
	}
}
