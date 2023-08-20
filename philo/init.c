/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kumamon <kumamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:44:40 by seok              #+#    #+#             */
/*   Updated: 2023/08/20 09:47:34 by kumamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	init_args(int ac, char *av[], t_arg *arg)
{
	if (ac < 5 || ac > 6)
		return (false);
	arg->total_philo = my_atoi(av[1]);
	arg->time_to_die = my_atoi(av[2]);
	arg->time_to_eat = my_atoi(av[3]);
	arg->time_to_sleep = my_atoi(av[4]);
	arg->must_eat = 0;
	arg->av_option = false;
	if (av[5] != NULL)
	{
		arg->must_eat = my_atoi(av[5]);
		arg->av_option = true;
	}
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

t_fork *init_fork(t_arg *arg)
{
	int 	i;
	t_fork	*fork;

	fork = malloc(sizeof(t_fork) * arg->total_philo);
	if (fork == FAIL)
		return (NULL);
	i = -1;
	while (++i < arg->total_philo)
	{
		pthread_mutex_init(&fork[i].mutex, NULL);
		fork[i].status = UNLOCK;
		fork[i].num = i;
	}
	return (fork);
}

void	init_philo_arg(t_arg *arg, t_philo *philo, t_fork *fork)
{
	philo->arg = arg;
	philo->eat_cnt = 0;
	philo->fork[LEFT] = &fork[philo->name];
	philo->fork[RIGHT] = &fork[(philo->name + 1) % arg->total_philo];
	printf("--- philo[%d]_fork idx----\n", philo->name);
	printf("\tL[%d] R[%d]\n", philo->name, (philo->name + 1) % arg->total_philo);
	// philo->fork[LEFT]->num = philo->name;
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
		printf("1[%d_] : %p\n", i, &philo[i]);
		philo[i].tid = malloc(sizeof(pthread_t));
		if (philo[i].tid == FAIL)
			return (ft_free(philo[i].tid), false);
		philo[i].name = i;
		init_philo_arg(arg, &philo[i], fork);
	printf("**fork : %p : %d\n", &fork[philo[i].name], fork[philo[i].name].num);
	printf("*philo : %p : %d\n", philo[i].fork[LEFT], philo[i].fork[LEFT]->num);
		if (pthread_create(&philo[i].tid, NULL, (void *)routine, &philo[i]))
			return (ft_free(philo[i].tid), false);
		usleep(1);
		i++;
	}
	return(true);
}
