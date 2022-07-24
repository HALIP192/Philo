/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:26:48 by ntitan            #+#    #+#             */
/*   Updated: 2022/07/24 13:27:14 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

uintmax_t	ft_time(void)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000000 + time.tv_usec);
}

void	error_msg(char *str)
{
	int	str_len;

	str_len = ft_strlen(str);
	write(1, str, str_len);
}

void	ft_free(t_data *data)
{
	free(data->pthreads);
	free(data->mutex_s);
}

int	malloc_data(t_data *data)
{
	data->pthreads = (pthread_t *)malloc(
			sizeof(pthread_t) * (data->phil_num + 1));
	data->mutex_s = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * data->phil_num);
	data->pthread_start = (uintmax_t *)malloc(
			sizeof(uintmax_t) * data->phil_num);
	data->eaten = (uint *)malloc(sizeof(uint) * data->phil_num);
	data->death_time = (uintmax_t *)malloc(
			sizeof(uintmax_t) * data->phil_num);
	data->mutex_eaten = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * (data->phil_num));
	if (data->pthreads && data->mutex_s && data->pthread_start
		&& data->eaten && data->death_time)
		return (0);
	ft_free(data);
	return (1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
