/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:27:34 by seok              #+#    #+#             */
/*   Updated: 2023/08/26 14:14:17 by seok             ###   ########.fr       */
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
	LIVE = 0,
	DEAD
}t_status;

typedef enum e_fork_flag
{
	LEFT = 0,
	RIGHT,
	UNLOCK,
	LOCK,
}t_fork_flag;

typedef struct s_fork
{
	t_fork_flag		status;
	pthread_mutex_t	mutex;
}t_fork;

typedef struct s_monitor
{
	pthread_mutex_t	mu_print;
	pthread_mutex_t	mu_dead;
	int				dead_flag;
	pthread_mutex_t	mu_all_eat;
	int				eat_cnt;
}t_monitor;

typedef struct s_arg
{
	int			total_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	int			av_option;
	int			print_dead;
	long long	start_time;
	t_monitor	monitor;
}t_arg;

typedef struct s_philo
{
	pthread_t		tid;
	int				name;
	int				eat_cnt;
	int				eat_finish;
	long long		last_eat_time;
	t_fork			*fork[2];
	t_arg			*arg;
}t_philo;

// behaivor.c
void		*routine(t_philo *philo);
int			dining(t_philo *philo);
void		eating(t_philo *philo);
int			sleeping(t_philo *philo);
void		thinking(t_philo *philo);

// fork.c
int			pick_up_fork(t_philo *philo, int flag);
void		put_down_fork(t_philo *philo, int flag);

// init.c
int			init_args(int ac, char *av[], t_arg *arg);
t_fork		*init_fork(t_arg *arg);
void		init_philo_arg(t_arg *arg, t_philo *philo, t_fork *fork);
int			init_philo(t_arg *arg, t_fork *fork);

// library.c
int			my_atoi(const char *str);
int			my_check_digit(const char *str);
size_t		ft_strlen(const char *s);

// monitor.c
int			monitoring(t_philo *philo);
int			is_dead(t_philo *philo);

// mutex.c
int			mutex_read(pthread_mutex_t *mutex, int *variable);
void		mutex_write(pthread_mutex_t *mutex, int *variable, int flag);
void		mutex_cnt(pthread_mutex_t *mutex, int *variable);

//  utils.c
long long	get_time(void);
int			ft_free(void *arg);
int			msleep(long long start, long long end, t_philo *philo);
void		print_shell(t_philo *philo, char *str);

#endif