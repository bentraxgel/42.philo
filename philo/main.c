/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:22:44 by seok              #+#    #+#             */
/*   Updated: 2023/08/24 16:23:43 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// void	pick_up_fork(t_philo *philo, int flag)
// {
// 	printf("philo_name : %d\n", philo->name + 1);
// 	if (flag == LEFT)
// 		printf("LEFT_%d\n", philo->fork[flag]->num);
// 	else
// 		printf("RIGHT_%d\n", philo->fork[flag]->num);
// 	pthread_mutex_lock(&philo->fork[flag]->mutex);
// 	if (philo->fork[flag]->status == UNLOCK)
// 	{
// 		philo->fork[flag]->status = LOCK;
// 		print_shell(philo, "has taken a fork");
// 		pthread_mutex_unlock(&philo->fork[flag]->mutex);
// 		return ;
// 	}
// 	pthread_mutex_unlock(&philo->fork[flag]->mutex);
// 	// usleep(500);
// 	// printf("END\n");
// }

	// pthread_mutex_lock(&philo->fork->mutex);
	// 	fork[LEFT]

int	main(int ac, char *av[])
{
	t_arg	arg;
	t_fork	*fork;

	if (init_args(ac, av, &arg) == false)
		return (printf(E_ARG));
	// 철학자 한명일 경우 예외처리 따로 해야함. // 에러가 아니고 
	fork = init_fork(&arg);
	if (fork == NULL)
		return (printf(E_ALLOC));
	if (init_philo(&arg, fork) == false)
		return (printf(E_ALLOC));
}
