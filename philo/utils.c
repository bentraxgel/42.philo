/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:54:02 by seok              #+#    #+#             */
/*   Updated: 2023/08/26 13:43:20 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000));
}

int	ft_free(void *arg)
{
	if (arg == 0)
		return (false);
	else
	{
		free(arg);
		return (true);
	}
}

int	msleep(long long start, long long end, t_philo *philo)
{
	while (get_time() - start < end)
	{
		if (is_dead(philo) == DEAD)
			return (DEAD);
		usleep(200);
	}
	if (is_dead(philo) == DEAD)
		return (DEAD);
	return (LIVE);
}

void	print_shell(t_philo *philo, char *str)
{
	long long	current_time;
	long long	print_time;

	pthread_mutex_lock(&philo->arg->monitor.mu_print);
	current_time = get_time();
	print_time = current_time - philo->arg->start_time;
	pthread_mutex_lock(&philo->arg->monitor.mu_dead);
	if (philo->arg->monitor.dead_flag == DEAD \
			&& philo->arg->print_dead == UNLOCK)
	{
		philo->arg->print_dead = LOCK;
		printf("\t\t%lld %d %s\n", print_time, philo->name + 1, "died");
	}
	else if (philo->arg->monitor.dead_flag == LIVE \
				&& philo->arg->print_dead == UNLOCK)
		printf("\t\t%lld %d %s\n", print_time, philo->name + 1, str);
	pthread_mutex_unlock(&philo->arg->monitor.mu_dead);
	pthread_mutex_unlock(&philo->arg->monitor.mu_print);
}
