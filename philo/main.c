/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kumamon <kumamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:22:44 by seok              #+#    #+#             */
/*   Updated: 2023/08/18 02:00:16 by kumamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (arg->total_philo <= 0 || arg->time_to_die <= 0 || \
		arg->time_to_eat <= 0 || arg->time_to_sleep <= 0 || arg->must_eat < 0)
		return (false);
	printf("%d, ", arg->total_philo);
	printf("%d, ", arg->time_to_die);
	printf("%d, ", arg->time_to_eat);
	printf("%d, ", arg->time_to_sleep);
	printf("%d\n", arg->must_eat);
	return (true);
}

int	main(int ac, char *av[])
{
	t_arg	arg;

	if (init_args(ac, av, &arg) == false)
		return (E_ARG);
	if ()
	// 철학자 한명일 경우 예외처리 따로 해야함.
	// if (arg.total_philo == 1)
	// 	return (0);
	init_philo;
}

void	init_philo()
{
	pthread_t	philo;
	
}