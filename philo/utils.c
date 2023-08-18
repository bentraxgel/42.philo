/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:54:02 by seok              #+#    #+#             */
/*   Updated: 2023/08/19 03:48:33 by seok             ###   ########.fr       */
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

void	print_shell(t_philo *philo, char *str)
{
	printf("shell : %lld\n", philo->arg->start_time);
	long long	current_time;
	long long	print_time;

	pthread_mutex_lock(&philo->arg->monitor.mu_print);
	current_time = get_time();
	printf(">> %lld - ", current_time);
	printf("%lld\n", philo->arg->start_time);
	print_time = current_time - philo->arg->start_time;
	printf(" = %lld\n", print_time);
	pthread_mutex_unlock(&philo->arg->monitor.mu_print);
	printf("%lld %d %s\n", print_time, philo->name + 1, str);
}

void	is_dead(t_philo *philo)
{
	long long	current_time;

	current_time = get_time();
	if (current_time - philo->last_eat_time >= philo->arg->time_to_die)
		philo->arg->monitor.dead_flag = DEAD;
	print_shell(philo, "died");
	// TODO +add : 포크 잡은 경우 drop_fork();
}

void	philos_usleep(int milli_seconds)
{
	long long	start;
	long long	end_time;

printf("sleep\n");
	start = get_time();
	end_time = start + milli_seconds;
	while (get_time() <= end_time)
	{
		usleep(300);
	}
}

void	drop_fork(t_philo *philo, int flag)
{
	printf("drop\n");
	pthread_mutex_lock(&philo->fork[flag]->mutex);
	if (philo->fork[flag]->status == LOCK)
		philo->fork[flag]->status = UNLOCK;
	pthread_mutex_unlock(&philo->fork[flag]->mutex);
}

void	eating(t_philo *philo)
{
	philo->eat_cnt++;
	print_shell(philo, "is eating");
	philo->last_eat_time = get_time();
	philos_usleep(philo->arg->time_to_eat);
	// usleep(50);
	drop_fork(philo, LEFT);
	drop_fork(philo, RIGHT);

}

void	sleeping(t_philo *philo)
{
	print_shell(philo, "is sleeping");
	philos_usleep(philo->arg->time_to_sleep);
}