/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:34:04 by seok              #+#    #+#             */
/*   Updated: 2023/08/14 22:58:54 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_atoi(const char *str, int ret)
{
	int			cnt;
	long long	result;

	cnt = 0;
	result = 0;
	while (*str == 32 || (8 < *str && *str < 14))
		str++;
	my_check_digit(str);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (false);
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		result = (result * 10) + *str - '0';
		str++;
		cnt++;
	}
	if (cnt > 10)
		return (false);
	return (result);
}
