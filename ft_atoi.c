/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 14:56:43 by ntitan            #+#    #+#             */
/*   Updated: 2022/07/23 21:29:35 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	ft_isspace(int c)
{
	return (c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v' || c == ' ');
}

int	ft_isdigit(int c)
{
	return (c <= '9' && c >= '0');
}

long long	ft_atol(const char *str)
{
	long long	result;
	long long	sign;

	if (str == NULL)
		return (0);
	result = 0;
	sign = 1;
	while (ft_isspace(*(str)))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
		result = result * 10 + (*str++ - '0');
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	return ((int) ft_atol(str));
}
