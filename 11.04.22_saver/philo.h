#ifndef PHILO_H
#define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft/libft.h"

//typedef struct timeval  time_t;
typedef  pthread_mutex_t t_mutex;
typedef pthread_t t_thread;
typedef struct timeval t_time;

typedef struct s_philo
{
	t_thread	id;
	t_time		last_dinner;
	int			n;
	int			dinner_counter;
	t_mutex	dining_mutex;
	t_mutex	*min_fork;
	t_mutex	*max_fork;
	struct s_vars	*vars;
	
}				t_philo;

typedef struct s_vars
{
//	number_of_philosophers time_to_die time_to_eat
//	time_to_sleep
//	[number_of_times_each_philosopher_must_eat]
	int	number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_lunches;
	t_time		start;
	t_mutex *forks;
	t_philo *philos;
	t_mutex print_mutex;
	int	counter;
	
}				t_vars;

void	mutex_creator(t_vars *vars);
void attribute_forks_to_philos(t_philo *philos, t_vars *vars);
void ft_sleep(long ms);
long get_time_gap_from_start(t_vars *vars);
long get_time_gap_from_dinner(t_philo philo);
void argv_parser(t_vars *vars, int argc, char **argv);




#endif
