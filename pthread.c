/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:36:31 by ntitan            #+#    #+#             */
/*   Updated: 2022/07/10 21:04:39 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef enum e_action
{
	RELEASE_FORK,
	TAKE_FORK
}	t_action;

void	*pthread_loop(size_t phil_num)
{
	t_data	*data;

	data = init_struct();
	data->pthread_start = ft_time();
	data->death_time[phil_num] = data->live_time;
	while (data->eaten[phil_num] < data->eat_num && !somebody_dead(data))
	{
		data->death_time[phil_num] = fork_action(TAKE_FORK, data) + data->live_time;
		mutex_print
	}
}
