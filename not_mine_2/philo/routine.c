/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblackth <lblackth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 15:29:20 by lblackth          #+#    #+#             */
/*   Updated: 2022/04/10 19:26:29 by lblackth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	forks_eating(t_phil *phil)
{
	pthread_mutex_lock(phil->lf);
	pthread_mutex_lock(phil->printm);
	gettimeofday(&(phil->tek), NULL);
	printf("%d %d has taken a fork\n", timeval_comp(phil->data->start, \
	phil->tek) / 1000, phil->n);
	pthread_mutex_unlock(phil->printm);
	pthread_mutex_lock(phil->rg);
	pthread_mutex_lock(phil->printm);
	gettimeofday(&(phil->tek), NULL);
	printf("%d %d has taken a fork\n%d %d is eating\n", \
	timeval_comp(phil->data->start, \
	phil->tek) / 1000, phil->n, timeval_comp(phil->data->start, \
	phil->tek) / 1000, phil->n);
	pthread_mutex_lock(phil->check);
	gettimeofday(&(phil->last), NULL);
	pthread_mutex_unlock(phil->check);
	pthread_mutex_unlock(phil->printm);
	ft_sleep(phil, phil->data->t_eat);
	pthread_mutex_lock(phil->printm);
	pthread_mutex_unlock(phil->lf);
	pthread_mutex_unlock(phil->rg);
}

void	sleeping_thinking(t_phil *phil)
{
	gettimeofday(&(phil->tek), NULL);
	printf("%d %d is sleeping\n", timeval_comp(phil->data->start, phil->tek) \
	/ 1000, phil->n);
	pthread_mutex_unlock(phil->printm);
	ft_sleep(phil, phil->data->t_sleep);
	pthread_mutex_lock(phil->printm);
	gettimeofday(&(phil->tek), NULL);
	printf("%d %d is thinking\n", timeval_comp(phil->data->start, phil->tek) \
	/ 1000, phil->n);
	pthread_mutex_unlock(phil->printm);
}

void	*routine(void *philo)
{
	t_phil	*phil;

	phil = (t_phil *)philo;
	while (phil->rep != 0)
	{
		forks_eating(phil);
		sleeping_thinking(phil);
		phil->rep--;
	}
	phil->data->done++;
	return (NULL);
}
