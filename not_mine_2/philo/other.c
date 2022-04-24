/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblackth <lblackth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:14:22 by lblackth          #+#    #+#             */
/*   Updated: 2022/04/10 16:38:21 by lblackth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	timeval_comp(struct timeval fst, struct timeval snd)
{
	return ((snd.tv_sec - fst.tv_sec) * 1000000 + snd.tv_usec - fst.tv_usec);
}

void	ft_sleep(t_phil *phil, int ms)
{
	struct timeval	tmp;

	gettimeofday(&tmp, NULL);
	while (timeval_comp(phil->tek, tmp) < ms * 1000)
	{
		usleep(20);
		gettimeofday(&tmp, NULL);
	}
}
