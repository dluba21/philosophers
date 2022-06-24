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



t_philo	*each_philo_and_checker_attributing(t_vars *vars, t_checker *checker_thread) //чекер отдельный поток, а основной - сам философ
{
	t_philo	*philo;
	
	philo = malloc(sizeof(t_philo));  //nado izbavitsya ot malloca
	if (!philo)
	{
		printf("philo malloc error\n");
		exit(1);
	}
	philo->vars = vars;
	philo->n = vars->current_philo_number;
	if (vars->dinner_number)
		philo->dinner_counter = vars->dinner_number;
	ft_sleep(5);
//	usleep(100);
//	gettimeofday(&vars->start, NULL);
	return (philo);
}



int	process_philos_part(t_vars *vars)
{
	int			ret_1;
	int			ret_2;
	t_checker	*checker_thread;
	t_philo		*philo;
	
	philo = each_philo_and_checker_attributing(vars, checker_thread); //nado izbavitsya ot malloca
	checker_thread->vars = vars;
	checker_thread->philo = philo;
	
	ret_1 = pthread_create(&checker_thread->id, NULL, checker_thread_func, \
			(void *)checker_thread);
	ret_2 = pthread_detach(checker_thread->id);
	if (ret_1 || ret_2)
	{
		printf("thread error\n");
		return (1);
	}
	routine_philo_func(philo);
	return (0);
}






//void	process_philos_part(t_vars *vars) //это если философ-поток в потоке отдельном
//{
//
//
//	ret_1 = pthread_create(&philo->id, NULL, routine_thread_func, \
//			(void *)philo);
//	ret_2 = pthread_detach(&philo->id);
//	if (ret_1 || ret_2)
//	{
//		printf("thread error\n");
//		return (1);
//	}
//}

//это если философ-поток в потоке отдельном
//void	each_philo_thread_attribute(t_vars *vars) //присваивание аттрибутов философу - треду, а сам процесс пусть и чекает, точнее основной поток процесса ребенка
//{
//	t_philo	*philo;
//
//	philo->vars = vars;
//	if (vars->dinner_counter)
//		philo->dinner_counter = vars->dinner_counter;
//}

int	semas_creator(t_vars *vars)
{
	
	
	vars->forks_sem = sem_open("/sem_1", O_CREAT | O_EXCL, 0666, vars->number_of_philosophers); //посмотреть как O_EXCL работает
	vars->print_bin_sem = sem_open("/sem_2", O_CREAT | O_EXCL, 0666, 1);
	vars->dinner_numb_bin_sem = sem_open("/sem_3", O_CREAT | O_EXCL, 0666, 1);
	vars->death_bin_sem = sem_open("/sem_4", O_CREAT | O_EXCL, 0666, 1);
	vars->first_dinner_sem = sem_open("/sem_5", O_CREAT | O_EXCL, 0666, 0);
	
	sem_unlink("/sem_1");
	sem_unlink("/sem_2");
	sem_unlink("/sem_3");
	sem_unlink("/sem_4");
	sem_unlink("/sem_5");
	
//	printf("%d\n", (int)vars->forks_sem);
//	printf("%d\n",  (int)vars->print_bin_sem);
//	printf("%d\n", (int)vars->dinner_numb_bin_sem);
//	printf("%d\n", (int)vars->death_bin_sem);
//
	if (vars->forks_sem == SEM_FAILED || vars->print_bin_sem == SEM_FAILED \
		|| vars->dinner_numb_bin_sem == SEM_FAILED || vars->death_bin_sem == SEM_FAILED)
		return (1);
	return (0);
}


int	process_philos_creator(t_vars *vars)
{
	int	i;
	int	pid;
	
	vars->pid_array = malloc(sizeof(int) * vars->number_of_philosophers);
	if (!vars->pid_array)
	{
		printf("malloc error pid_array\n");
		return (1);
	}
	
//	each_philo_thread_attribute(vars); //присвоить аттрибуты общему философу единственное отличие в номере филосоофа который передаю через счетчик
	
	i = 0;
	gettimeofday(&vars->start, NULL);
	while (i < vars->number_of_philosophers)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			
//			printf("child %d started\n", i);
			
			
			vars->current_philo_number = i; //узнаю номер философа
			process_philos_part(vars);
		}
//		printf("%d - %d\n", i, pid);
		vars->pid_array[i] = pid;
		i++;
	}
	
	printf("main process is sleeping\n");
//	sleep(1000);
	
	while (i--) //i--???
		waitpid(-1, NULL, 0);
	return (0);
}


int	philos_and_semas_init(t_vars *vars)
{

	if (semas_creator(vars))
	{
		printf("semas init error\n");
		exit (1);
	}
	if (process_philos_creator(vars))
	{
		printf("process_philos_creator error\n");
		exit (1);
	}
		//здесь надо проиницализировать все и оно скопируется в филос mainprocces
		//надо присвоить время первой хавки и тд а уже во время форков присвоить пиды и все
	return (0);
	
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
