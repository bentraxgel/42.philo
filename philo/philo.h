/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:27:34 by seok              #+#    #+#             */
/*   Updated: 2023/08/14 22:52:30 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>

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

}

// library.c
int	my_atoi(const char *str);

#endif