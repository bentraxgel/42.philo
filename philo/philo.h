/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kumamon <kumamon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:27:34 by seok              #+#    #+#             */
/*   Updated: 2023/08/16 11:41:59 by kumamon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
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

typedef struct s_src
{
	int	total_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	must_eat;
}t_src;

typedef struct s_philo
{
	
};

// library.c
// int	my_atoi(const char *str, int *ret);
int	my_atoi(const char *str);
int	my_check_digit(const char *str);
size_t	ft_strlen(const char *s);

// main.c
int	arg_exception(int ac, char *av[], t_src *src);

#endif