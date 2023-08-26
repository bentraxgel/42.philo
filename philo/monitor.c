/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:40:39 by seok              #+#    #+#             */
/*   Updated: 2023/08/26 13:43:14 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	is_dead(t_philo *philo)
{
	long long	current_time;

	current_time = get_time();
	if (current_time - philo->last_eat_time >= philo->arg->time_to_die)
	{
		mutex_write(&philo->arg->monitor.mu_dead, \
					&philo->arg->monitor.dead_flag, DEAD);
		print_shell(philo, "died");
		return (DEAD);
	}
	return (LIVE);
}
