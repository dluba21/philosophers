/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lblackth <lblackth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 22:20:10 by lblackth          #+#    #+#             */
/*   Updated: 2022/04/10 15:50:55 by lblackth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <unistd.h> 
# include "libft/libft.h"

typedef struct s_phil
{
	pthread_mutex_t	*lf;
	pthread_mutex_t	*rg;
	pthread_mutex_t	*printm;
	pthread_mutex_t	*check;
	pthread_t		self;
	struct timeval	tek;
	struct timeval	last;
	int				n;
	int				rep;
	struct s_gen	*data;
}				t_phil;

typedef struct s_gen
{
	int				t_eat;
	int				t_sleep;
	int				t_die;
	int				num;
	int				rep;
	int				done;
	pthread_mutex_t	*vilki;
	pthread_mutex_t	*checks;
	pthread_mutex_t	printm;
	t_phil			*phils;
	struct timeval	start;
}				t_gen;

int		phils_init(t_gen *data);
int		phil_init(t_gen *data, int i);
int		mutex_init(t_gen *data);
void	av_to_data(int ac, char **av, t_gen *data);
void	doa_check(t_gen *data);
void	*routine(void *phil);
void	sleeping_thinking(t_phil *phil);
void	forks_eating(t_phil *phil);
void	ft_sleep(t_phil *phil, int ms);
int		timeval_comp(struct timeval fst, struct timeval snd);

#endif
