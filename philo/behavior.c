/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:17:10 by seok              #+#    #+#             */
/*   Updated: 2023/08/25 13:58:27 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine(t_philo *philo)
{
	//TODO 짝수애들 먹는시간 /2만큼 재우기
	if ((philo->name + 1) % 2 == 0)
		msleep(philo->last_eat_time, philo->arg->time_to_eat / 2, philo);
		// msleep(get_time(), philo->arg->time_to_eat / 2, philo);
		// msleep(mutex_long_read(&philo->mu_time, &philo->last_eat_time), philo->arg->time_to_eat / 2, philo);
	while (true)
	{
		// if (monitoring(philo) == DEAD)
		// 	return ;
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


int	pick_up_fork(t_philo *philo, int flag)
{
	while (true)
	{
		if (monitoring(philo) == DEAD)
			return (DEAD);
		pthread_mutex_lock(&philo->fork[flag]->mutex);
		if (philo->fork[flag]->status == UNLOCK)
		{
			philo->fork[flag]->status = LOCK;
			print_shell(philo, "has taken a fork");
			pthread_mutex_unlock(&philo->fork[flag]->mutex);
			return (LIVE);
		}
		pthread_mutex_unlock(&philo->fork[flag]->mutex);
		// usleep(200); //TODO&
	}
}

void	put_down_fork(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->fork[flag]->mutex);
	philo->fork[flag]->status = UNLOCK;
	pthread_mutex_unlock(&philo->fork[flag]->mutex);
}


int	dining(t_philo *philo)
{
	if (pick_up_fork(philo, LEFT) == DEAD)
		return (DEAD);
	if (pick_up_fork(philo, RIGHT) == DEAD)
		return (DEAD);
	eating(philo);
	put_down_fork(philo, RIGHT);
	put_down_fork(philo, LEFT);
	return (LIVE);
}
// int	dining(t_philo *philo)
// {
// 	// printf("%d-->dinig1\n", philo->name + 1); //&&
// 	pthread_mutex_lock(&philo->fork[LEFT]->mutex);
// 	philo->fork[LEFT]->status = LOCK;
// 	if (print_shell(philo, "has taken a fork") == false)
// 		return (DEAD);
// 	// printf("dinig2\n"); //&&
// 	pthread_mutex_lock(&philo->fork[RIGHT]->mutex);
// 	philo->fork[RIGHT]->status = LOCK;
// 	if (print_shell(philo, "has taken a fork") == false)
// 		return (DEAD);
// 	eating(philo);
// 	philo->fork[LEFT]->status = UNLOCK;
// 	philo->fork[RIGHT]->status = UNLOCK;
// 	pthread_mutex_unlock(&philo->fork[LEFT]->mutex);
// 	pthread_mutex_unlock(&philo->fork[RIGHT]->mutex);
// 	if (mutex_read(&philo->arg->monitor.mu_dead, &philo->arg->monitor.dead_flag) == DEAD)
// 		return (DEAD);
// 	return (LIVE);
// }

void	eating(t_philo *philo)
{
	// mutex_long_write(&philo->mu_time, &philo->last_eat_time, get_time());
	// printf("eating1\n"); //&&
	// pthread_mutex_lock(&philo->mu_time);
	// pthread_mutex_unlock(&philo->mu_time);
	philo->last_eat_time = get_time();
	monitoring(philo);

	if (print_shell(philo, "is eating") == false)
		return ;

	// if (msleep(mutex_long_read(&philo->mu_time, &philo->last_eat_time), philo->arg->time_to_eat, philo) == DEAD)
	// printf("%d---->eating2\n", philo->name); //&&
	// pthread_mutex_lock(&philo->mu_time);
	// if (msleep(philo->last_eat_time, philo->arg->time_to_eat, philo) == DEAD)
	if (msleep(get_time(), philo->arg->time_to_eat, philo) == DEAD)
	{
		// pthread_mutex_unlock(&philo->mu_time);
		return ;
	}
	// pthread_mutex_unlock(&philo->mu_time);
	// printf("**eating OUT\n"); //&&
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

	start_sleep = get_time();
	monitoring(philo);
	if (print_shell(philo, "is sleeping") == false)
		return (DEAD);
	msleep(start_sleep, philo->arg->time_to_sleep, philo);
	// if (mutex_read(&philo->arg->monitor.mu_dead, &philo->arg->monitor.dead_flag) == DEAD)
	// 	return (DEAD);
	return (LIVE);
}

int	thinking(t_philo *philo)
{
	monitoring(philo);
	if (print_shell(philo, "is thinking") == false)
		return (DEAD);
	// usleep(100);
	// if (mutex_read(&philo->arg->monitor.mu_dead, &philo->arg->monitor.dead_flag) == DEAD)
	// 	return (DEAD);
	return (LIVE);
}
