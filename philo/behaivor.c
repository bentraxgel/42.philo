/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behaivor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:28:15 by seok              #+#    #+#             */
/*   Updated: 2023/08/26 13:44:25 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(t_philo *philo)
{
	if ((philo->name + 1) % 2 == 0)
		msleep(philo->last_eat_time, philo->arg->time_to_eat / 2, philo);
	while (true)
	{
		if (monitoring(philo) == DEAD)
			return (0);
		if (philo->arg->total_philo == 1)
		{
			pick_up_fork(philo, LEFT);
			msleep(get_time(), philo->arg->time_to_die, philo);
			return (0);
		}
		if (philo->eat_finish == UNLOCK)
		{
			if (dining(philo) == DEAD)
				return (0);
			if (sleeping(philo) == DEAD)
				return (0);
			thinking(philo);
		}
	}
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

void	eating(t_philo *philo)
{
	if (monitoring(philo) == DEAD)
		return ;
	philo->last_eat_time = get_time();
	print_shell(philo, "is eating");
	if (msleep(philo->last_eat_time, philo->arg->time_to_eat, philo) == DEAD)
		return ;
	philo->eat_cnt++;
	if (philo->arg->av_option == true && philo->eat_cnt == philo->arg->must_eat)
	{
		mutex_cnt(&philo->arg->monitor.mu_all_eat, \
					&philo->arg->monitor.eat_cnt);
	}
}

int	sleeping(t_philo *philo)
{
	long long	start_sleep;

	start_sleep = get_time();
	if (monitoring(philo) == DEAD)
		return (DEAD);
	print_shell(philo, "is sleeping");
	if (msleep(start_sleep, philo->arg->time_to_sleep, philo) == DEAD)
		return (DEAD);
	return (LIVE);
}

void	thinking(t_philo *philo)
{
	if (monitoring(philo) == DEAD)
		return ;
	print_shell(philo, "is thinking");
}
