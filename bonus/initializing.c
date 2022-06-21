/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrdeysuvorov <anrdeysuvorov@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 22:59:23 by anrdeysuvor       #+#    #+#             */
/*   Updated: 2022/05/29 22:59:25 by anrdeysuvor      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"








void	process_philos_part(t_vars *vars)
{

	
	ret_1 = pthread_create(&philo->id, NULL, routine_thread_func, \
			(void *)philo);
	ret_2 = pthread_detach(&philo->id);
	if (ret_1 || ret_2)
	{
		printf("thread error\n");
		return (1);
	}
}

void	each_philo_thread_attribute(t_vars *vars) //присваивание аттрибутов философу - треду, а сам процесс пусть и чекает, точнее основной поток процесса ребенка
{
	t_philo	*philo;

	philo->vars = vars;
	if (vars->dinner_counter)
		philo->dinner_counter = vars->dinner_counter;
}

int	semas_creator(t_vars *vars)
{
	
//	sem_t	*dinner_numb_sem; //lishniy ne nado peredelivat bilo
//	t_time	start; //before fork
//	t_mutex	*forks; //
//	t_philo	*philos;
////	t_mutex	print_mutex; //semaphore n = 1
//	sem_t	*print_bin_sem;
////	t_mutex	dining_number_mutex; //semaphore n = 1
//	sem_t	*dining_numb_bin_sem;
////	int		not_hungry_yet; //semaphore n = 0
//	sem_t	*death_bin_sem;
	
	vars->forks_sem = sem_open("/sem_1", O_CREAT | O_EXCEL, 0666, vars->number_of_philosophers);
	vars->print_bin_sem = sem_open("/sem_2", O_CREAT | O_EXCEL, 0666, 1);
	vars->dining_numb_bin_sem = sem_open("/sem_3", O_CREAT | O_EXCEL, 0666, 1);
	vars->death_bin_sem = sem_open("/sem_4", O_CREAT | O_EXCEL, 0666, 1);
	if (vars->forks_sem == SEM_FAILED || vars->print_bin_sem == SEM_FAILED \
		|| vars->dining_numb_bin_sem == SEM_FAILED || vars->death_bin_sem == SEM_FAILED)
		return (1);
	return (0);
}

//int attach_attributes_to_philos(t_vars *vars)
//{
//	vars->
//}

int	philos_creator(t_vars *vars)
{
	int	i;
	int	pid;
	
	vars->pid_array = malloc(sizeof(int) * vars->number_of_philosophers);
	if (!vars->pid_array)
	{
		printf("malloc error pid_array\n");
		return (1);
	}
	
	each_philo_thread_attribute(vars); //присвоить аттрибуты общему философу единственное отличие в номере филосоофа который передаю через счетчик
	
	i = 0;
	while (i < vars->number_of_philosophers)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			philo->n = i; //узнаю номер философа
			process_philos_part(vars);
		}
		vars->pid_array[i] = pid;
		i++;
	}
	while (i--) //i--???
		waitpid(-1, NULL, 0);
}


int	philos_and_semas_init(t_vars *vars)
{

	if (semas_creator(t_vars *vars))
	{
		printf("semas init error\n");
		exit();
	}
	
	if (philos_creator(t_vars *vars))
		
		//здесь надо проиницализировать все и оно скопируется в филос mainprocces
		//надо присвоить время первой хавки и тд а уже во время форков присвоить пиды и все
		
	if (main_philos_process)
		
	
	
}





long	ft_time(void)
{
	struct timeval	tv;
	long			res;

	gettimeofday(&tv, NULL);
	res = 1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000;
	return (res);
}

void	ft_sleep(long ms)
{
	long	time;

	time = ft_time();
	usleep(ms * 850);
	while (ft_time() < time + ms)
		usleep(ms * 3);
}

long	get_time_gap_from_start(t_vars *vars)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - \
			(vars->start.tv_sec * 1000 + \
			vars->start.tv_usec / 1000));
}

long	get_time_gap_from_dinner(t_philo philo)
{
	t_time	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000 - \
			(philo.last_dinner.tv_sec * 1000 + \
			philo.last_dinner.tv_usec / 1000));
}








//
//
//
//void	print_with_mutex(char *str, t_philo *philo)
//{
//	pthread_mutex_lock(&(philo->vars->print_mutex));
//	printf("%ld %d %s", get_time_gap_from_start(philo->vars), \
//			philo->n + 1, str);
//	pthread_mutex_unlock(&(philo->vars->print_mutex));
//}
//
//int	philos_init(t_vars *vars)
//{
//	vars->philos = (t_philo *)malloc(sizeof(t_philo) * \
//					vars->number_of_philosophers);
//	if (!vars->philos)
//	{
//		printf("thread creating error: can't malloc\n");
//		return (1);
//	}
//	attribute_forks_to_philos(vars->philos, vars);
//	return (0);
//}
//
//int	philos_creator(t_vars *vars)
//{
//	int	ret_1;
//	int	ret_2;
//	int	i;
//
//	i = 0;
//	if (philos_init(vars))
//		return (1);
//	gettimeofday(&(vars->start), NULL);
//	while (i < vars->number_of_philosophers)
//	{
//		ret_1 = pthread_create(&(vars->philos[i].id), NULL, philo_func, \
//				(void *)&(vars->philos[i]));
//		ret_2 = pthread_detach(vars->philos[i].id);
//		if (ret_1 || ret_2)
//		{
//			free(vars->philos);
//			printf("thread error\n");
//			return (1);
//		}
//		i++;
//	}
//	return (0);
//}
