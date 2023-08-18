/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:54:02 by seok              #+#    #+#             */
/*   Updated: 2023/08/18 23:27:42 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time()
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
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

void	print_shell(t_philo *philo, char *str)
{
	long long	current_time;
	long long	print_time;

	pthread_mutex_lock(&philo->arg->monitor.mu_print);
	current_time = get_time();
	print_time = current_time - philo->arg->start_time;
	pthread_mutex_unlock(&philo->arg->monitor.mu_print);
	printf("%lld %d %s\n", print_time, philo->name, str);
}

void	is_dead(t_philo *philo)
{
	if (current_time - philo->last_eat_time >= philo->arg->time_to_die)
		philo->arg->monitor.dead_flag == DEAD;
	print_shell(philo, "died");
}

void	eating(t_philo *philo)
{
	print_time(philo, "is eating");
}

void	sleeping(t_philo *philo)
{
	print_time(philo, "is sleeping");
}