/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:59:34 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/05/29 22:59:34 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft/libft.h"

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef struct timeval	t_time;

typedef struct s_philo
{
	t_thread		pid;
	
	
	t_time			last_dinner;
	int				n;
	int				dinner_counter;
//	t_mutex			dining_mutex; //mb semaphore n = 1
	sem_t			*dining_bin_sem;
//	t_mutex			*min_fork;
//	t_mutex			*max_fork;
//	int				fork_min;
//	int				fork_max;
	struct s_vars	*vars;
}				t_philo;

typedef struct s_vars
{
	int		number_of_philosophers; //+
	int		time_to_die; //+
	int		time_to_eat; //+
	int		time_to_sleep; //+
//	int		dinner_number; //semaphore n = dinner_number
	sem_t	*dinner_numb_sem;
	t_time	start; //before fork
	t_mutex	*forks; //
	t_philo	*philos;
//	t_mutex	print_mutex; //semaphore n = 1
	sem_t	*print_bin_sem;
//	t_mutex	dining_number_mutex; //semaphore n = 1
	sem_t	*dining_numb_bin_sem;
//	int		not_hungry_yet; //semaphore n = 0
	sem_t	*death_bin_sema;
}				t_vars;

int		mutex_creator(t_vars *vars);
void	attribute_forks_to_philos(t_philo *philos, t_vars *vars);
void	ft_sleep(long ms);
long	get_time_gap_from_start(t_vars *vars);
long	get_time_gap_from_dinner(t_philo philo);
int		argv_parser(t_vars *vars, int argc, char **argv);
void	print_with_mutex(char *str, t_philo *philo);
int		philos_init(t_vars *vars);
int		philos_creator(t_vars *vars);
void	*philo_func(void *data);
#endif
