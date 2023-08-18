/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:22:44 by seok              #+#    #+#             */
/*   Updated: 2023/08/19 03:42:33 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitoring(t_philo *philo)
{
	int	flag;

	flag = LIVE;
	pthread_mutex_lock(&philo->arg->monitor.mu_dead);
	if (philo->arg->monitor.dead_flag == DEAD)
		flag = DEAD;
	pthread_mutex_unlock(&philo->arg->monitor.mu_dead);
	if (flag == DEAD)
		return (flag);
	
	pthread_mutex_lock(&philo->arg->monitor.mu_all_eat);
	if (philo->arg->monitor.eat_cnt == philo->arg->total_philo)
		flag = DEAD;
	pthread_mutex_unlock(&philo->arg->monitor.mu_all_eat);
	if (flag == DEAD)
		return (flag);
	return (flag);
}

void	pick_up_fork(t_philo *philo, int flag)
{
	printf("pick\n");
	printf("num : %d_%d\n", philo->fork[flag]->num, flag);
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
	printf("routine : %lld\n", philo->arg->start_time);
	if (philo->name % 2 == 0)
			usleep(500);
	while (1)
	{
		if (monitoring(philo) == DEAD)
			return (ERROR);
		//왼쪽 포크 집기
		pick_up_fork(philo, LEFT);
			// pick_up_fork(philo, RIGHT);
		//--->대기
		//오른쪽 포크 집기
		if (philo->fork[LEFT]->status == LOCK)
			pick_up_fork(philo, RIGHT);
		if (philo->arg->must_eat > 0)
		{
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
	// 철학자 한명일 경우 예외처리 따로 해야함.
	if (arg.total_philo == 1)
		return (usleep(arg.time_to_die), printf("one_philo\n"));
	fork = init_fork(&arg);
	if (fork == NULL)
		return (printf(E_ALLOC));
	if (init_philo(&arg, fork) == false)
		return (printf(E_ALLOC));
}