/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:01:45 by seok              #+#    #+#             */
/*   Updated: 2023/08/26 12:47:14 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_read(pthread_mutex_t *mutex, int *variable)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *variable;
	pthread_mutex_unlock(mutex);
	return (ret);
}

void	mutex_write(pthread_mutex_t *mutex, int *variable, int flag)
{
	pthread_mutex_lock(mutex);
	*variable = flag;
	pthread_mutex_unlock(mutex);
}

void	mutex_cnt(pthread_mutex_t *mutex, int *variable)
{
	pthread_mutex_lock(mutex);
	*variable += 1;
	pthread_mutex_unlock(mutex);
}
