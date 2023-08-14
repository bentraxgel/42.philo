/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:22:44 by seok              #+#    #+#             */
/*   Updated: 2023/08/14 23:12:01 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_src	src;
	int		i;
	if (ac < 5 || ac > 6)
	{
		printf("ERROR : The arguments is not satisfied.\n");
		return (false);
	}
	i = 0;
	if (my_atoi(av[i], ) == false)
		return (false);
	printf("%d, ", src.total_philo);
	printf("%d, ", src.time_to_die);
	printf("%d, ", src.time_to_eat);
	printf("%d, ", src.time_to_sleep);
	printf("%d\n", src.must_eat);
	return (true);
}