/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dluba <dluba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 03:00:47 by dluba             #+#    #+#             */
/*   Updated: 2022/07/01 03:00:47 by dluba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_period(t_philo *philo)
{
	sem_wait(philo->vars->forks_sem);
	print_with_sema("has taken a fork\n", philo);
	sem_wait(philo->vars->forks_sem);
	print_with_sema("has taken a fork\n", philo);
	gettimeofday(&(philo->last_dinner), NULL);
	print_with_sema("is eating\n", philo);
	ft_sleep(philo->vars->time_to_eat);
	sem_post(philo->vars->forks_sem);
	sem_post(philo->vars->forks_sem);
}

void	*routine_philo_func(t_philo *philo)
{
	if ((philo->n + 1) % 2 == 0)
		usleep(1000);
	while (1)
	{
		eating_period(philo);
		if (!(--philo->dinner_counter))
		{
			free(philo->vars->pid_array);
			free(philo->checker_thread);
			free(philo);
			exit (0);
		}
		print_with_sema("is sleeping\n", philo);
		ft_sleep(philo->vars->time_to_sleep);
		print_with_sema("is thinking\n", philo);
	}
	return (NULL);
}

void	checker_thread_free(t_checker *checker_thread)
{
	free(checker_thread->vars->pid_array);
	free(checker_thread->philo);
	free(checker_thread);
}

void	*checker_thread_func(void *data)
{
	int			i;
	int			n;
	t_checker	*checker_thread;

	checker_thread = (t_checker *)data;
	n = checker_thread->vars->number_of_philosophers;
	ft_sleep(500);
	while (1)
	{
		i = 0;
		while (i < n)
		{
			ft_sleep(1);
			if (get_time_gap_from_dinner(*checker_thread->philo) > \
							checker_thread->vars->time_to_die)
			{
				sem_wait(checker_thread->vars->death_bin_sem);
				print_with_sema("died\n", checker_thread->philo);
				checker_thread_free(checker_thread);
				exit (1);
			}
			i++;
		}
	}
}
