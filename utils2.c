/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 20:09:57 by ntitan            #+#    #+#             */
/*   Updated: 2022/07/23 20:10:13 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	eaten_action(t_data *data, size_t phil_num)
{
	pthread_mutex_lock(data->mutex_eaten + phil_num);
	data->eaten[phil_num] += 1;
	pthread_mutex_unlock(data->mutex_eaten + phil_num);
}

int big_mutex_init(t_data *data)
{
	int	mutex_error;
	int i;

	i = 0;
	mutex_error = 0;
	while (i < (int)data->phil_num)
	{
		mutex_error |= pthread_mutex_init(data->mutex_s + i, NULL);
		mutex_error |= pthread_mutex_init(data->mutex_eaten + i++, NULL);
	}
	return (mutex_error);
}