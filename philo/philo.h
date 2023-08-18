/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:27:34 by seok              #+#    #+#             */
/*   Updated: 2023/08/18 22:25:19 by seok             ###   ########.fr       */
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
# define FAIL	0
# define E_ARG "ERROR : The arguments is not satisfied.\n"
# define E_ALLOC "ERROR : The allocate is failed.\n"

typedef enum e_status
{
	DEAD = 0,
	LIVE
}t_status;

typedef enum e_fork_flag
{
	LEFT = 0,
	RIGHT,
	LOCK,
	UNLOCK
}t_fork_flag;

typedef struct s_fork
{
	int				status;
	pthread_mutex_t	mutex;
}t_fork;

/*
쓰레드마다 pc레지스터를 독립할당한다
- pc 레지스터 : 스레드가 명령어의 어디까지 수행했는지 나타냄.
스레드가 어느부분까지 수행했느지 기억하기 위해 pc레지스터를 독립할당해야함.
->TODO 철학자가 뭐했는지에 대해 표시할 필요있음.
*/

typedef struct s_arg
{
	int			total_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	long long	start_time;
	t_monitor	monitor;
}t_arg;

typedef	struct s_monitor
{
	pthread_mutex_t	mu_print;
	pthread_mutex_t	mu_dead;
	int				dead_flag;
	pthread_mutex_t	mu_all_eat;
	int				eat_cnt;
}t_monitor;

typedef struct s_philo
{
	pthread_t		tid;
	int				name;
	int				eat_cnt;
	long long		last_eat_time;
	t_fork			fork[2];
	t_arg			*arg;
}t_philo;


// library.c
int	my_atoi(const char *str);
int	my_check_digit(const char *str);
size_t	ft_strlen(const char *s);

// main.c
int		monitoring(t_philo *philo);
void	routine(t_philo *philo);

// init.c
int	init_args(int ac, char *av[], t_arg *arg);

//  utils.c
long long	get_time();
int			ft_free(void *arg);

#endif