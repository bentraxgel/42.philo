/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:44:40 by seok              #+#    #+#             */
/*   Updated: 2023/08/18 22:30:48 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	init_args(int ac, char *av[], t_arg *arg)
{
	int		i;

	if (ac < 5 || ac > 6)
		return (false);
	arg->total_philo = my_atoi(av[1]);
	arg->time_to_die = my_atoi(av[2]);
	arg->time_to_eat = my_atoi(av[3]);
	arg->time_to_sleep = my_atoi(av[4]);
	if (av[5] != NULL)
		arg->must_eat = my_atoi(av[5]);
	arg->start_time = get_time();
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

int	init_fork(t_arg *arg, t_fork *fork)
{
	int 	i;

	fork = malloc(sizeof(t_fork) * arg->total_philo);
	if (fork == FAIL)
		return (false);
	i = 0;
	while (i < arg->total_philo)
	{
		pthread_mutex_init(&fork[i].mutex, NULL);
		fork[i].status = UNLOCK;
	}
	return (true);
}

void	init_philo_arg(t_arg *arg, t_philo *philo, t_fork *fork)
{
	philo->arg = arg;
	philo->eat_cnt = 0;
	philo->fork[LEFT] = fork[philo->name];
	philo->fork[RIGHT] = fork[(philo->name + 1) % arg->total_philo];
}

int	init_philo(t_arg *arg, t_fork *fork)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = malloc(sizeof(t_philo) * arg->total_philo);
	if (philo == FAIL)
		return (ft_free(philo), false);
	while (i < arg->total_philo)
	{
		philo[i].tid = malloc(sizeof(pthread_t));
		if (philo[i].tid == FAIL)
			return (ft_free(philo[i].tid), false);
		philo[i].name = i + 1;
		init_philo_arg(arg, &philo[i], fork);
		if (pthread_create(&philo[i].tid, NULL, (void *)routine, &philo[i]))
			return (ft_free(philo[i].tid), false);
		usleep(1 * 1000);
		i++;
	}
}