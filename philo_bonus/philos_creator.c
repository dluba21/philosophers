/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 03:00:44 by dluba             #+#    #+#             */
/*   Updated: 2022/07/01 03:00:45 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	process_philos_creator(t_vars *vars)
{
	int	i;

	vars->pid_array = malloc(sizeof(int) * vars->number_of_philosophers);
	if (!vars->pid_array)
	{
		printf("malloc error pid_array\n");
		return (1);
	}
	i = process_philos_creator_2(vars);
	process_philos_creator_3(vars, i);
	return (0);
}

int	process_philos_creator_2(t_vars *vars)
{
	int	i;
	int	pid;

	i = 0;
	gettimeofday(&vars->start, NULL);
	vars->start.tv_usec += 5000;
	while (i < vars->number_of_philosophers)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			vars->current_philo_number = i;
			process_philos_part(vars);
		}
		vars->pid_array[i] = pid;
		i++;
	}
	return (i);
}

int	process_philos_creator_3(t_vars *vars, int i)
{
	int	status;

	status = -1;
	while (i)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 0)
			i--;
		else if (WEXITSTATUS(status) == 1)
			break ;
	}
	i = 0;
	while (i < vars->number_of_philosophers)
		kill(vars->pid_array[i++], SIGKILL);
	free(vars->pid_array);
	return (0);
}
