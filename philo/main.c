/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:22:44 by seok              #+#    #+#             */
/*   Updated: 2023/08/26 13:55:27 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	int		i;
	t_arg	arg;
	t_fork	*fork;

	if (init_args(ac, av, &arg) == false)
		return (printf(E_ARG));
	fork = init_fork(&arg);
	if (fork == NULL)
		return (printf(E_ALLOC));
	if (init_philo(&arg, fork) == false)
		return (printf(E_ALLOC));
	pthread_mutex_destroy(&arg.monitor.mu_print);
	pthread_mutex_destroy(&arg.monitor.mu_dead);
	pthread_mutex_destroy(&arg.monitor.mu_all_eat);
	i = 0;
	while (i < arg.total_philo)
		pthread_mutex_destroy(&fork[i++].mutex);
	free(fork);
}
