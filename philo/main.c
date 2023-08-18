/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:22:44 by seok              #+#    #+#             */
/*   Updated: 2023/08/18 23:28:11 by seok             ###   ########.fr       */
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
	pthread_mutex_lock(&philo->fork[flag].mutex);
	if (philo->fork[flag].status == UNLOCK)
	{
		philo->fork[flag].status = LOCK;
		print_shell(philo, "has taken a fork");
	}
	pthread_mutex_unlock(&philo->fork[flag].mutex);
}

void	routine(t_philo *philo)
{
	if (monitoring == DEAD)
		return (ERROR);
	//왼쪽 포크 집기
	pick_up_fork(philo, LEFT);

	//--->대기
	//오른쪽 포크 집기
	if (philo->fork[LEFT].status == LOCK)
		pick_up_fork(philo, RIGHT);
	if (philo->arg->must_eat > 0)
	{
		if (philo->eat_cnt < philo->arg->must_eat)
		{
			eating(philo);
			sleeping(philo);
		}
		if (is_dead(philo) == DEAD)
			return (ERROR);
		print_shell(philo, "is thinking");
	}
	else
	{
		eating(philo);
		sleeping(philo);
		if (is_dead(philo) == DEAD)
			return (ERROR);
		print_shell(philo, "is thinking");
	}

/*
1. 포크를 잡았는데 죽은경우 포크 반환
2. 철학자 한명일 경우 포크 잡고 죽을때까지 대기
*/
	return (NULL);
}

	// pthread_mutex_lock(&philo->fork->mutex);
	// 	fork[LEFT]

int	ft_free(void *mem, int i)
{
	int	j;

	j = -1;
	if (i == ERROR)
		free(mem);
	while (++j < i)
		free(&mem[i]);
	return (false);
}

int	main(int ac, char *av[])
{
	t_arg	arg;
	t_fork	fork;
	t_philo	philo;

	if (init_args(ac, av, &arg) == false)
		return (printf(E_ARG));
	printf("total : %d\n", arg.total_philo); //TODO del
	// if ()
	// 철학자 한명일 경우 예외처리 따로 해야함.
	if (arg.total_philo == 1)
		return (usleep(arg.time_to_die),);
	if (init_fork(&arg, &fork) == false)
		return (printf(E_ALLOC));
	if (init_philo(&philo, &fork) == false)
		return (printf(E_ALLOC));