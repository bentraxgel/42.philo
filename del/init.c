/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:44:40 by seok              #+#    #+#             */
/*   Updated: 2023/08/20 19:43:26 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

long long	get_time()
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return ((long long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

int	init_args(int ac, char *av[], t_arg *arg)
{
	if (ac < 5 || ac > 6)
		return (false);
	arg->total_philo = my_atoi(av[1]);
	arg->time_to_die = my_atoi(av[2]);
	arg->time_to_eat = my_atoi(av[3]);
	arg->time_to_sleep = my_atoi(av[4]);
	arg->must_eat = 0;
	if (av[5] != NULL)
		arg->must_eat = my_atoi(av[5]);
	arg->start_time = get_time();
	// printf("*start : %lld\n", arg->start_time);
	if (arg->total_philo <= 0 || arg->time_to_die <= 0 || \
		arg->time_to_eat <= 0 || arg->time_to_sleep <= 0 || arg->must_eat < 0)
		return (false);
	arg->monitor.dead_flag = LIVE;
	arg->monitor.eat_cnt = 0;
	pthread_mutex_init(&arg->monitor.mu_print, NULL);
	pthread_mutex_init(&arg->monitor.mu_dead, NULL);
	pthread_mutex_init(&arg->monitor.mu_all_eat, NULL);
	return (true);
}

void	print_(t_arg *arg)
{
	printf("%d, %d, %d, %d, ", arg->total_philo, arg->time_to_die, arg->time_to_eat, arg->time_to_sleep);
	printf("%d\n", arg->must_eat);
	printf("start : %lld\n", arg->start_time);
	printf("monitor : %d %d\n", arg->monitor.dead_flag, arg->monitor.eat_cnt);
}

// void	print_(t_philo *philo)
// {
// 	printf("%d, %d, %d, %d, ", philo->arg->total_philo, philo->arg->time_to_die, philo->arg->time_to_eat, philo->arg->time_to_sleep);
// 	printf("%d\n", philo->arg->must_eat);
// 	printf("start : %lld\n", philo->arg->start_time);
// 	printf("monitor : %d %d\n", philo->arg->monitor.dead_flag, philo->arg->monitor.eat_cnt);
// }
