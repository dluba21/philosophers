/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblackth <lblackth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:33:59 by lblackth          #+#    #+#             */
/*   Updated: 2022/04/10 16:57:28 by lblackth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	av_to_data(int ac, char **av, t_gen *data)
{
	data->num = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->rep = ft_atoi(av[5]);
}

int	mutex_init(t_gen *data)
{
	int	i;

	data->vilki = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* data->num);
	if (!data->vilki)
		return (0);
	data->checks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* data->num);
	if (!data->checks)
		return (0);
	i = 0;
	while (i < data->num)
	{
		if (pthread_mutex_init(data->vilki + i, NULL))
			return (0);
		if (pthread_mutex_init(data->checks + i, NULL))
			return (0);
		++i;
	}
	return (1);
}

int	phil_init(t_gen *data, int i)
{
	data->phils[i].data = data;
	data->phils[i].printm = &(data->printm);
	data->phils[i].check = data->checks + i;
	data->phils[i].n = i + 1;
	data->phils[i].lf = data->vilki + i;
	data->phils[i].rep = data->rep;
	data->phils[i].last = data->start;
	if (i != data->num - 1)
		data->phils[i].rg = data->vilki + i + 1;
	else
		data->phils[i].rg = data->vilki;
	if (pthread_create(&(data->phils[i].self), NULL, routine, \
	(void *)((data->phils) + i)))
		return (0);
	return (1);
}

int	phils_init(t_gen *data)
{
	int	i;

	data->phils = (t_phil *)malloc(sizeof(t_phil) * data->num);
	if (!data->phils)
		return (0);
	i = 0;
	gettimeofday(&(data->start), NULL);
	while (i < data->num)
	{
		if (!phil_init(data, i))
			return (0);
		i += 2;
	}
	usleep(500);
	i = 1;
	while (i < data->num)
	{
		if (!phil_init(data, i))
			return (0);
		i += 2;
	}
	usleep(500);
	return (1);
}

int	main(int ac, char **av)
{
	t_gen	data;

	memset(&data, 0, sizeof(t_gen));
	if (ac == 5 || ac == 6)
	{
		av_to_data(ac, av, &data);
		if (!data.rep)
			data.rep = -1;
		pthread_mutex_init(&(data.printm), NULL);
		if (!mutex_init(&data))
			return (0);
		if (!phils_init(&data))
			return (0);
		doa_check(&data);
		free(data.checks);
		free(data.phils);
		free(data.vilki);
	}
	return (0);
}
