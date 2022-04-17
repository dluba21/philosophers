/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblackth <lblackth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:40:52 by lblackth          #+#    #+#             */
/*   Updated: 2022/04/10 17:27:30 by lblackth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	doa_check(t_gen *data)
{
	struct timeval	tmp;
	int				i;

	i = 0;
	while (1)
	{
		gettimeofday(&tmp, NULL);
		pthread_mutex_lock(data->phils[i].check);
		if (timeval_comp(data->phils[i].last, tmp) / 1000 > data->t_die \
		&& data->phils[i].rep)
		{
			pthread_mutex_lock(&(data->printm));
			printf("%d %d died\n", timeval_comp(data->start, tmp) \
			/ 1000, i + 1);
			break ;
		}
		if (data->done == data->num)
			break ;
		pthread_mutex_unlock(data->phils[i].check);
		i = (i + 1) % data->num;
	}
}
