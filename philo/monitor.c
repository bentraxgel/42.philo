/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 13:22:44 by seok              #+#    #+#             */
/*   Updated: 2023/08/24 19:40:21 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//TODO 반환값 생기게하자
int	is_dead(t_philo *philo)
{
	long long	current_time;
	// long long	philo_eat_time;

	if (mutex_read(&philo->arg->monitor.mu_dead, &philo->arg->monitor.dead_flag) == DEAD)
		return (DEAD);
	// philo_eat_time = mutex_long_read(&philo->mu_time, &philo->last_eat_time);
	pthread_mutex_lock(&philo->mu_time);
	current_time = get_time();
	// if (current_time - philo_eat_time >= philo->arg->time_to_die)
	if (current_time - philo->last_eat_time >= philo->arg->time_to_die)
	{
		pthread_mutex_unlock(&philo->mu_time);
		print_shell(philo, "died");
		mutex_write(&philo->arg->monitor.mu_dead, \
					&philo->arg->monitor.dead_flag, DEAD);
		return (DEAD);
	}
	pthread_mutex_unlock(&philo->mu_time);
	return (LIVE);
}

int	monitoring(t_philo *philo)
{
	if (mutex_read(&philo->arg->monitor.mu_dead, \
		&philo->arg->monitor.dead_flag) == DEAD)
		return (DEAD);
	if (mutex_read(&philo->arg->monitor.mu_all_eat, \
		&philo->arg->monitor.eat_cnt) == philo->arg->total_philo)
		return (DEAD);
	if (is_dead(philo) == DEAD)
		return (DEAD);
	return (LIVE);
}
void	thread_manager(t_philo *philo)
{
	int i;

	while (true)
	{
		i = -1;
		while (++i < philo->arg->total_philo)
		{
			if (is_dead(&philo[i]) == DEAD)
				return ;
		}
	}
}
