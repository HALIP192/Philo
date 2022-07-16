/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 14:34:02 by ntitan            #+#    #+#             */
/*   Updated: 2022/07/16 15:42:47 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int somebody_dead(t_data *data)
{
	int ret;

	pthread_mutex_lock(&data->dead_mutex);
	ret = data->stop;
	pthread_mutex_unlock(&data->dead_mutex);
	return (ret);
}

void	ft_putunbr(char *dest, uint src)
{
	dest[8] = n % 10 + '0';
	n = n / 10;
	dest[7] = n % 10 + '0';
	n = n / 10;
	dest[6] = n % 10 + '0';
	n = n / 10;
	dest[5] = n % 10 + '0';
	n = n / 10;
	dest[4] = n % 10 + '0';
	n = n / 10;
	dest[3] = n % 10 + '0';
	n = n / 10;
	dest[2] = n % 10 + '0';
	n = n / 10;
	dest[1] = n % 10 + '0';
	n = n / 10;
	dest[0] = n % 10 + '0';
}

void	ft_usleep(useconds_t usec)
{
	struct timeval	start;
	struct timeval	step;
	
	
	gettimeofday(&start, NULL);
	usleep(usec * 9 / 10);
	gettimeofday(&step, NULL);
	while ((size_t)(((size_t)(step.tv_sec - start.tv_sec)) * 1000000 +
			((size_t)(step.tv_usec - start.tv_usec))) < usec)
	{
		usleep(100);
		gettimeofday(&step, NULL);
	}

}

void	end_philo(t_data *data)
{
	uint	i;

	i = 0;
	while (i < data->phil_num)
	{
		pthread_join(data->pthreads[i], NULL);
		pthread_mutex_destroy(data->mutex_s + i++);
	}
	pthread_join(data->ptreads[data->phil_num], NULL);
	pthread_mutex_destroy(&data->dead_mutex);
	ft_free(data);
}
