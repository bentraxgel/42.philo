/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:01:45 by seok              #+#    #+#             */
/*   Updated: 2023/08/24 22:54:52 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_read(pthread_mutex_t *mutex, int *variable)
{
	int ret;


// printf("mutex1\n"); //&&
	pthread_mutex_lock(mutex);
	ret = *variable;
	pthread_mutex_unlock(mutex);
	return (ret);
}

// 스레드가 공유하는 자원에 원하는 값을 써주는 함수
void	mutex_write(pthread_mutex_t *mutex, int *variable, int flag)
{
	// printf("mutex2\n"); //&&
	pthread_mutex_lock(mutex);
	*variable = flag;
	pthread_mutex_unlock(mutex);
}

int	mutex_long_read(pthread_mutex_t *mutex, long long *variable)
{
	int ret;

// printf("mutex3\n"); //&&
	pthread_mutex_lock(mutex);
	ret = *variable;
	pthread_mutex_unlock(mutex);
	return (ret);
}

// 스레드가 공유하는 자원에 원하는 값을 써주는 함수
void	mutex_long_write(pthread_mutex_t *mutex, long long *variable, long long flag)
{
	// printf("mutex4\n"); //&&
	pthread_mutex_lock(mutex);
	*variable = flag;
	pthread_mutex_unlock(mutex);
}

//TODO add -> mutex_cnt() ->다먹은 철학자 명수 올려주는 것.
void	mutex_cnt(pthread_mutex_t *mutex, int *variable)
{
	// printf("mutex5\n"); //&&
	pthread_mutex_lock(mutex);
	variable++;
	pthread_mutex_unlock(mutex);
}