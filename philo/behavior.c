/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:17:10 by seok              #+#    #+#             */
/*   Updated: 2023/08/24 19:45:38 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *philo)
{
	//TODO 짝수애들 먹는시간 /2만큼 재우기`
	if ((philo->name + 1) % 2 == 0)
		msleep(mutex_long_read(&philo->mu_time, &philo->last_eat_time), philo->arg->time_to_eat / 2, philo);
	while (true)
	{
		if (monitoring(philo) == DEAD)
			return ;
			// return (DEAD);
		if (philo->arg->total_philo == 1)
		{
			mutex_write(&philo->fork[LEFT]->mutex, &philo->fork[LEFT]->status, LOCK);
			if (print_shell(philo, "has taken a fork") == false)
				return ;
			msleep(get_time(), philo->arg->time_to_die, philo);
			is_dead(philo);
			return ;
		}
		if (philo->eat_finish == UNLOCK)
		{
			if (dining(philo) == DEAD)
				return ;
			if (sleeping(philo) == DEAD)
				return ;
			if (thinking(philo) == DEAD)
				return ;
		}
	}

/*
1. 포크를 잡았는데 죽은경우 포크 반환
2. 철학자 한명일 경우 포크 잡고 죽을때까지 대기
*/
	return ;
	// return (true);
}


int	dining(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork[LEFT]->mutex);
	philo->fork[LEFT]->status = LOCK;
	if (print_shell(philo, "has taken a fork") == false)
		return (DEAD);
	// if (philo->fork[LEFT]->status == LOCK)
	// {
		pthread_mutex_lock(&philo->fork[RIGHT]->mutex);
		philo->fork[RIGHT]->status = LOCK;
		if (print_shell(philo, "has taken a fork") == false)
			return (DEAD);
		eating(philo);
		philo->fork[LEFT]->status = UNLOCK;
		philo->fork[RIGHT]->status = UNLOCK;
		pthread_mutex_unlock(&philo->fork[RIGHT]->mutex);
	// }
	pthread_mutex_unlock(&philo->fork[LEFT]->mutex);
	if (mutex_read(&philo->arg->monitor.mu_dead, &philo->arg->monitor.dead_flag) == DEAD)
		return (DEAD);
	return (LIVE);
}

void	eating(t_philo *philo)
{
	// mutex_long_write(&philo->mu_time, &philo->last_eat_time, get_time());
	pthread_mutex_lock(&philo->mu_time);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->mu_time);
	monitoring(philo);

	if (print_shell(philo, "is eating") == false)
		return ;

	// if (msleep(mutex_long_read(&philo->mu_time, &philo->last_eat_time), philo->arg->time_to_eat, philo) == DEAD)
	pthread_mutex_lock(&philo->mu_time);
	if (msleep(philo->last_eat_time, philo->arg->time_to_eat, philo) == DEAD)
	{
		pthread_mutex_unlock(&philo->mu_time);
		return ;
	}
	pthread_mutex_unlock(&philo->mu_time);
	philo->eat_cnt++;
	if (philo->arg->av_option == true && philo->eat_cnt >= philo->arg->must_eat)
	{
		philo->eat_finish = LOCK;
		mutex_cnt(&philo->arg->monitor.mu_all_eat, &philo->arg->monitor.eat_cnt);
	}
}

int	sleeping(t_philo *philo)
{
	long long	start_sleep;

	monitoring(philo);
	if (print_shell(philo, "is sleeping") == false)
		return (DEAD);
	start_sleep = get_time();
	msleep(start_sleep, philo->arg->time_to_sleep, philo);
	if (mutex_read(&philo->arg->monitor.mu_dead, &philo->arg->monitor.dead_flag) == DEAD)
		return (DEAD);
	return (LIVE);
}

int	thinking(t_philo *philo)
{
	monitoring(philo);
	if (print_shell(philo, "is thinking") == false)
		return (DEAD);
	usleep(200);
	if (mutex_read(&philo->arg->monitor.mu_dead, &philo->arg->monitor.dead_flag) == DEAD)
		return (DEAD);
	return (LIVE);
}
