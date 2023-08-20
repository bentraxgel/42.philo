/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:22:44 by seok              #+#    #+#             */
/*   Updated: 2023/08/20 23:03:34 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring(t_philo *philo)
{
	if (mutex_read(&philo->arg->monitor.mu_dead, &philo->arg->monitor.dead_flag) == DEAD)
		return (DEAD);
	if (mutex_read(&philo->arg->monitor.mu_all_eat, &philo->arg->monitor.eat_cnt) == philo->arg->total_philo)
		return (DEAD);
	return (LIVE);
}

void	pick_up_fork(t_philo *philo, int flag)
{
	printf("philo_name : %d\n", philo->name + 1);
	// printf("pick\n");
	if (flag == LEFT)
		printf("LEFT_%d\n", philo->fork[flag]->num);
	else
		printf("RIGHT_%d\n", philo->fork[flag]->num);
	pthread_mutex_lock(&philo->fork[flag]->mutex);
	if (philo->fork[flag]->status == UNLOCK)
	{
		philo->fork[flag]->status = LOCK;
		print_shell(philo, "has taken a fork");
		pthread_mutex_unlock(&philo->fork[flag]->mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->fork[flag]->mutex);
	// usleep(500);
	// printf("END\n");
}

int	routine(t_philo *philo)
{
	printf("routine ->");
	printf("R[%d] : %p\n", philo->name, philo);
	printf("*routine : %lld\n", philo->arg->start_time);
	// if (philo->n`(500);
	while (1)
	{
		printf("TIME : %lld\n",get_time() - philo->arg->start_time);
		if (monitoring(philo) == DEAD)
		{
			printf(">>>monitor\n");
			return (ERROR);
		}
		pick_up_fork(philo, LEFT);
		if (philo->fork[LEFT]->status == LOCK)
			pick_up_fork(philo, RIGHT);
		if (philo->arg->av_option == true)
		{
			printf("IF\n");
			if (philo->eat_cnt < philo->arg->must_eat)
			{
				eating(philo);
				sleeping(philo);
			}
			is_dead(philo);
			print_shell(philo, "is thinking");
		}
		else
		{
			printf("ELSE\n");
			eating(philo);
			sleeping(philo);
			is_dead(philo);
			print_shell(philo, "is thinking");
		}
	}

/*
1. 포크를 잡았는데 죽은경우 포크 반환
2. 철학자 한명일 경우 포크 잡고 죽을때까지 대기
*/
	return (true);
}

	// pthread_mutex_lock(&philo->fork->mutex);
	// 	fork[LEFT]

int	main(int ac, char *av[])
{
	t_arg	arg;
	t_fork	*fork;

	if (init_args(ac, av, &arg) == false)
		return (printf(E_ARG));
	// 철학자 한명일 경우 예외처리 따로 해야함. // 에러가 아니고 
	if (arg.total_philo == 1)
		return (usleep(arg.time_to_die), printf("one_philo\n"));
	fork = init_fork(&arg);
	if (fork == NULL)
		return (printf(E_ALLOC));
	if (init_philo(&arg, fork) == false)
		return (printf(E_ALLOC));
}

int	msleep(long long start, long long end, t_philo *philo)
{
	while (get_time() - start < end)
	{
		if (is_dead(philo) == DEAD)
			return (false);
		usleep(100);
	}
	return (true);
}