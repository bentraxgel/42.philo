/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:54:02 by seok              #+#    #+#             */
/*   Updated: 2023/08/24 22:55:00 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time()
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((long long)((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000));
}

int ft_free(void *arg)
{
	if (arg == 0)
		return (false);
	else
	{
		free(arg);
		return (true);
	}
}

int	print_shell(t_philo *philo, char *str)
{
	long long	current_time;
	long long	print_time;
	// printf("print_shell\n"); //&&
	pthread_mutex_lock(&philo->arg->monitor.mu_print);
	if (mutex_read(&philo->arg->monitor.mu_dead, &philo->arg->monitor.dead_flag) == DEAD)
	{
		pthread_mutex_unlock(&philo->arg->monitor.mu_print);
		return (false);
	}
	// usleep(100);
	current_time = get_time();
	print_time = current_time - philo->arg->start_time;
	printf("\t\t%lld %d %s\n", print_time, philo->name + 1, str);
	pthread_mutex_unlock(&philo->arg->monitor.mu_print);
	return (true);
}

int	msleep(long long start, long long end, t_philo *philo)
{
	while (get_time() <= end + start)
	// while (get_time() - start <= end)
	{
		if (is_dead(philo) == DEAD)
			return (DEAD);
		usleep(300);
	}
	return (LIVE);
}

// int	msleep(long long start, long long end, t_philo *philo)
// {
// 	(void)start;
// 	long long cur = get_time();
// 	while (get_time() <= cur + end)
// 	{
// 		if (is_dead(philo) == DEAD)
// 			return (DEAD);
// 		usleep(300);
// 	}
// 	return (LIVE);
// }




// void	drop_fork(t_philo *philo, int flag)
// {
// 	printf("drop\n");
// 	pthread_mutex_lock(&philo->fork[flag]->mutex);
// 	if (philo->fork[flag]->status == LOCK)
// 		philo->fork[flag]->status = UNLOCK;
// 	pthread_mutex_unlock(&philo->fork[flag]->mutex);
// }
