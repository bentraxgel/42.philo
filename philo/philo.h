/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kumamon <kumamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:27:34 by seok              #+#    #+#             */
/*   Updated: 2023/08/18 02:00:16 by kumamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>

# define ERROR -1
# define E_ARG "ERROR : The arguments is not satisfied.\n"

typedef enum e_status
{
	EAT = 0,
	SLEEP,
	THINK
}t_status;

typedef struct s_arg
{
	int	total_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}t_arg;

typedef	struct s_data
{
	double	start_time; //TODO 자료형뭐?
	// 다먹은 시간??
	// 포크?
}t_data;
/*
쓰레드마다 pc레지스터를 독립할당한다
- pc 레지스터 : 스레드가 명령어의 어디까지 수행했는지 나타냄.
스레드가 어느부분까지 수행했느지 기억하기 위해 pc레지스터를 독립할당해야함.
->TODO 철학자가 뭐했는지에 대해 표시할 필요있음.
*/

typedef struct s_philo
{
	pthread_t	philo_id;
	int			philo_num;
	int			eat_cnt;
	long long	last_eat_time;
	t_arg		arg;
}t_philo;

typedef	struct s_monitor
{
	pthread_mutex_t	print;
	pthread_mutex_t	fork;
	int				must_eat_flag;
	int				dead_flag;

}t_monitor;


// library.c
// int	my_atoi(const char *str, int *ret);
int	my_atoi(const char *str);
int	my_check_digit(const char *str);
size_t	ft_strlen(const char *s);

// main.c
int	init_args(int ac, char *av[], t_arg *arg);

#endif