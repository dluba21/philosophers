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
//	vars->first_dinner_sem = sem_open("/sem_5", O_CREAT | O_EXCL, 0666, 0);
	
	sem_unlink("/sem_1");
	sem_unlink("/sem_2");
	sem_unlink("/sem_3");
	sem_unlink("/sem_4");
//	sem_unlink("/sem_5");
	
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
	int	status;
	
	status = -1;
	vars->pid_array = malloc(sizeof(int) * vars->number_of_philosophers);
	if (!vars->pid_array)
	{
		printf("malloc error pid_array\n");
		return (1);
	}
	
//	each_philo_thread_attribute(vars); //присвоить аттрибуты общему философу единственное отличие в номере филосоофа который передаю через счетчик
	
	i = 0;
//

	
//==46158== HEAP SUMMARY:
//==46158==     in use at exit: 23,245 bytes in 167 blocks
//==46158==   total heap usage: 188 allocs, 21 frees, 31,693 bytes allocated
//==46158==
//==46158== LEAK SUMMARY:
//==46158==    definitely lost: 16 bytes in 1 blocks
//==46158==    indirectly lost: 0 bytes in 0 blocks
//==46158==      possibly lost: 8,840 bytes in 7 blocks
//==46158==    still reachable: 14,389 bytes in 159 blocks
//==46158==         suppressed: 0 bytes in 0 blocks
//==46158== Rerun with --leak-check=full to see details of leaked memory
//==46158==
//==46158== For lists of detected and suppressed errors, rerun with: -s
//==46158== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 398 from 10)
	
//==46525== HEAP SUMMARY:
//==46525==     in use at exit: 23,229 bytes in 166 blocks
//==46525==   total heap usage: 188 allocs, 22 frees, 31,693 bytes allocated
//==46525==
//==46525== LEAK SUMMARY:
//==46525==    definitely lost: 0 bytes in 0 blocks
//==46525==    indirectly lost: 0 bytes in 0 blocks
//==46525==      possibly lost: 8,840 bytes in 7 blocks
//==46525==    still reachable: 14,389 bytes in 159 blocks
//==46525==         suppressed: 0 bytes in 0 blocks
//==46525== Rerun with --leak-check=full to see details of leaked memory
//==46525==
//==46525== For lists of detected and suppressed errors, rerun with: -s

	
	
	
	
	gettimeofday(&vars->start, NULL);
	vars->start.tv_usec += 5000; //убираю погрешность в начале почтии в 5 милисекунд
	while (i < vars->number_of_philosophers)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			
//			printf("child %d started\n", i);
			
//			sleep(1000);
			vars->current_philo_number = i; //узнаю номер философа
			process_philos_part(vars);
		}
//		printf("%d - %d\n", i, pid);
		vars->pid_array[i] = pid;
		i++;
	}
	printf("i = %d\n", i);
	
	
	printf("main process      [%d] is sleeping\n", getpid());
	
//	sleep(10);
//	printf("\n\n\nwant to kill\n\n\n\n");
	printf("make return of process pid_1 = %d\n", getpid());
	while (i)
	{
	
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 0) //0 dlya obeda
		{
//			printf("\n[status_of_dinner numb = %d]\n", status);
//				printf("i = %d\n", i);
			i--;
		}
		else if (WEXITSTATUS(status) == 1) //1 dlya smerti
		{
//			printf("\n[status_of_dying = %d]\n", status);
			break;
		}
			
	}
//	printf("make return of process pid_2 = %d\n", getpid());
//	sem_wait(philo->vars->vars->death_bin_sem);
//	printf("before kill!!!\n\n\n");
	i = 0;
	while (i < vars->number_of_philosophers)
		kill(vars->pid_array[i++], SIGKILL);
	free(vars->pid_array);
	

	while (i--) //i--???
		waitpid(-1, NULL, 0);
//	sleep(300);


	

	printf("ret_2 = %d\n", sem_close(vars->forks_sem));
	printf("ret_2 = %d\n", sem_close(vars->print_bin_sem));
	printf("ret_2 = %d\n", sem_close(vars->dinner_numb_bin_sem));
	printf("ret_2 = %d\n", sem_close(vars->death_bin_sem));
	

	return (0);
}


int	philos_and_semas_init(t_vars *vars)
{

	if (semas_creator(vars))
	{
		printf("semas init error\n");
		exit (1);
	}
//	if (process_philos_creator(vars))
//	{
//		
//		exit (1);
//	}
		//здесь надо проиницализировать все и оно скопируется в филос mainprocces
		//надо присвоить время первой хавки и тд а уже во время форков присвоить пиды и все
	return (0);
	
}



