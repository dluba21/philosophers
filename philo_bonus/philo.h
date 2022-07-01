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
# include <semaphore.h>
# include <signal.h>

typedef pthread_mutex_t	t_mutex;
typedef pthread_t		t_thread;
typedef struct timeval	t_time;

typedef struct s_philo
{
	t_time				last_dinner;
	int					n;
	int					dinner_counter;
	struct s_vars		*vars;
	struct s_checker	*checker_thread;
}				t_philo;

typedef struct s_checker
{
	t_philo			*philo;
	struct s_vars	*vars;
	t_thread		id;
}				t_checker;

typedef struct s_vars
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		*pid_array;
	int		dinner_number;
	int		dinner_counter;
	t_time	start;
	t_philo	*philos;
	int		current_philo_number;
	int		not_hungry_yet;
	sem_t	*forks_sem;
	sem_t	*print_bin_sem;
	sem_t	*dinner_numb_sem;
	sem_t	*dinner_numb_bin_sem;
	sem_t	*dinner_bin_sem;
	sem_t	*death_bin_sem;
	sem_t	*first_dinner_sem;
}				t_vars;

void	ft_sleep(long ms);
long	ft_time(void);
long	get_time_gap_from_start(t_vars *vars);
long	get_time_gap_from_dinner(t_philo philo);
t_philo	*each_philo_and_checker_attr(t_vars *vars);
int		process_philos_part(t_vars *vars);
int		semas_creator(t_vars *vars);
int		process_philos_creator(t_vars *vars);
int		philos_and_semas_init(t_vars *vars);
void	print_with_sema(char *str, t_philo *philo);
int		argv_parser(t_vars *vars, int argc, char **argv);
void	eating_period(t_philo *philo);
void	*routine_philo_func(t_philo *philo);
void	*checker_thread_func(void *data);
int		process_philos_creator_2(t_vars *vars);
int		process_philos_creator_3(t_vars *vars, int i);
void	checker_thread_free(t_checker *checker_thread);
int		ft_atoi(const char *str);
#endif
