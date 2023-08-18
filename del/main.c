/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:22:44 by seok              #+#    #+#             */
/*   Updated: 2023/08/19 04:31:00 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_arg	arg;
	// t_fork	*fork;

	if (init_args(ac, av, &arg) == false)
		return (printf(E_ARG));
	print_(&arg);
	// 철학자 한명일 경우 예외처리 따로 해야함.
	// if (arg.total_philo == 1)
	// 	return (usleep(arg.time_to_die), printf("one_philo\n"));
	// fork = init_fork(&arg);
	// if (fork == NULL)
	// 	return (printf(E_ALLOC));
	if ( init_philo(&arg, fork) == false)
		return (printf(E_ALLOC));
}