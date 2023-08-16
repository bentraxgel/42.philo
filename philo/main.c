/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kumamon <kumamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:22:44 by seok              #+#    #+#             */
/*   Updated: 2023/08/16 11:40:30 by kumamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_exception(int ac, char *av[], t_src *src)
{
	int		i;

	if (ac < 5 || ac > 6)
		return (false);
	src->total_philo = my_atoi(av[1]);
	src->time_to_die = my_atoi(av[2]);
	src->time_to_eat = my_atoi(av[3]);
	src->time_to_sleep = my_atoi(av[4]);
	if (av[5] != NULL)
		src->must_eat = my_atoi(av[5]);
	if (src->total_philo <= 0 || src->time_to_die <= 0 || \
		src->time_to_eat <= 0 || src->time_to_sleep <= 0 || src->must_eat < 0)
		return (false);
	printf("%d, ", src->total_philo);
	printf("%d, ", src->time_to_die);
	printf("%d, ", src->time_to_eat);
	printf("%d, ", src->time_to_sleep);
	printf("%d\n", src->must_eat);
	return (true);
}

int	main(int ac, char *av[])
{
	t_src	src;

	if (arg_exception(ac, av, &src) == false)
		return (E_ARG);
	if ()
}