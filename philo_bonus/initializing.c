/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:59:23 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/07/01 03:00:32 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*each_philo_and_checker_attr(t_vars *vars)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
	{
		printf("philo malloc error\n");
		exit(1);
	}
	philo->vars = vars;
	philo->n = vars->current_philo_number;
	if (vars->dinner_number)
		philo->dinner_counter = vars->dinner_number;
	ft_sleep(5);
	return (philo);
}

int	process_philos_part(t_vars *vars)
{
	int			ret_1;
	int			ret_2;
	t_checker	*checker_thread;
	t_philo		*philo;

	checker_thread = (t_checker *)malloc(sizeof(t_checker));
	philo = each_philo_and_checker_attr(vars);
	checker_thread->vars = vars;
	checker_thread->philo = philo;
	philo->checker_thread = checker_thread;
	ret_1 = pthread_create(&checker_thread->id, NULL, checker_thread_func, \
			(void *)checker_thread);
	ret_2 = pthread_detach(checker_thread->id);
	if (ret_1 || ret_2)
	{
		printf("thread error\n");
		return (1);
	}
	routine_philo_func(philo);
	return (0);
}

int	semas_creator(t_vars *vars)
{
	vars->forks_sem = sem_open("/sem_1", O_CREAT | O_EXCL, 0666, \
						vars->number_of_philosophers);
	vars->print_bin_sem = sem_open("/sem_2", O_CREAT | O_EXCL, 0666, 1);
	vars->dinner_numb_bin_sem = sem_open("/sem_3", O_CREAT | O_EXCL, 0666, 1);
	vars->death_bin_sem = sem_open("/sem_4", O_CREAT | O_EXCL, 0666, 1);
	sem_unlink("/sem_1");
	sem_unlink("/sem_2");
	sem_unlink("/sem_3");
	sem_unlink("/sem_4");
	if (vars->forks_sem == SEM_FAILED || vars->print_bin_sem == SEM_FAILED \
		|| vars->dinner_numb_bin_sem == SEM_FAILED || \
		vars->death_bin_sem == SEM_FAILED)
		return (1);
	return (0);
}
