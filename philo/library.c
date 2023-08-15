/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seok <seok@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 21:34:04 by seok              #+#    #+#             */
/*   Updated: 2023/08/15 18:54:14 by seok             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	int	idx;

	idx = 0;
	if (s == 0)
		return (0);
	while (s[idx])
		idx++;
	return ((size_t) idx);
}

int	my_check_digit(const char *str)
{
	if (ft_strlen(str) != 1 && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			return (false);
		str++;
	}
	while (*str)
	{
		if ('0' <= *str && *str <= '9')
			str++;
		else
			return (false);
	}
	return (true);
}

int	my_atoi(const char *str)
{
	int			cnt;
	long long	result;

	cnt = 0;
	result = 0;
	while (*str == 32 || (8 < *str && *str < 14))
		str++;
	if (my_check_digit(str) == false)
		return (ERROR);
	if (*str == '-' || *str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		result = (result * 10) + *str - '0';
		str++;
		cnt++;
	}
	if (cnt > 10 || result == 0)
		return (ERROR);
	return ((int)result);
}

// int	my_atoi(const char *str, int *ret)
// {
// 	int			cnt;
// 	long long	result;

// 	cnt = 0;
// 	result = 0;
// 	while (*str == 32 || (8 < *str && *str < 14))
// 		str++;
// 	if (my_check_digit(str) == false)
// 		return (false);
// 	if (*str == '-' || *str == '+')
// 		str++;
// 	while ('0' <= *str && *str <= '9')
// 	{
// 		result = (result * 10) + *str - '0';
// 		str++;
// 		cnt++;
// 	}
// 	if (cnt > 10 || result == 0)
// 		return (false);
// 	*ret = (int)result;
// 	return (true);
// }
