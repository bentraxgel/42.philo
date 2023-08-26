/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 19:46:58 by seok              #+#    #+#             */
/*   Updated: 2023/08/25 19:49:24 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pick_up_fork(t_philo *philo, int flag)
{
	while (true)
	{
		pthread_mutex_lock(&philo->fork[flag]->mutex);
		if (monitoring(philo) == DEAD || philo->eat_finish == LOCK)
		{
			pthread_mutex_unlock(&philo->fork[flag]->mutex);
			return (DEAD);
		}
		if (philo->fork[flag]->status == UNLOCK)
		{
			philo->fork[flag]->status = LOCK;
			print_shell(philo, "has taken a fork");
			pthread_mutex_unlock(&philo->fork[flag]->mutex);
			return (LIVE);
		}
		pthread_mutex_unlock(&philo->fork[flag]->mutex);
		usleep(100);
	}
}

void	put_down_fork(t_philo *philo, int flag)
{
	pthread_mutex_lock(&philo->fork[flag]->mutex);
	philo->fork[flag]->status = UNLOCK;
	pthread_mutex_unlock(&philo->fork[flag]->mutex);
}
