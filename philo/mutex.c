/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:01:45 by seok              #+#    #+#             */
/*   Updated: 2023/08/20 20:56:29 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mutex_read(pthread_mutex_t *mutex, int *variable)
{
	int ret;

	pthread_mutex_lock(mutex);
	ret = *variable;
	pthread_mutex_unlock(mutex);
	return (ret);
}

// 스레드가 공유하는 자원에 원하는 값을 써주는 함수
void mutex_write(pthread_mutex_t *mutex, int *variable, int flag)
{
	pthread_mutex_lock(mutex);
	*variable = flag;
	pthread_mutex_unlock(mutex);
}
