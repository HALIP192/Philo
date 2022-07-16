/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:36:31 by ntitan            #+#    #+#             */
/*   Updated: 2022/07/16 15:46:51 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

typedef enum e_action
{
	RELEASE_FORK,
	TAKE_FORK
}	t_action;

uintmax_t	fork_action(int action, t_data *data, uint phil_num)
{
	uintmax_t	time;

	if (action)
	{
		pthread_mutex_lock(data->mutex_s + phil_num);
		if (data->phil_num == 1)
		{
			ft_usleep(data->live_time + 100);
			return (0);
		}
		mutex_print(ft_time() - data->pthread_start[phil_num], phil_num,
							"has taken L fork");
		pthread_mutex_lock(data->mutex_s + (phil_num + 1) % data->phil_num);
		time = ft_time() - data->pthread_start[phil_num];
		mutex_print(time, phil_num, "has taken R fork");
		return (time);
	}
	else
	{
		pthread_mutex_unlock(data->mutex_s + phil_num);
		pthread_mutex_unlock(data->mutex_s + (phil_num + 1) % data->phil_num);
		return (0);
	}

}

void	*pthread_loop(size_t phil_num)
{
	t_data	*data;

	data = init_struct();
	data->pthread_start[phil_num] = ft_time();
	data->death_time[phil_num] = data->live_time;
	while (data->eaten[phil_num] < data->eat_num && !somebody_dead(data))
	{
		data->death_time[phil_num] = fork_action(TAKE_FORK, data, phil_num) + data->live_time;
		mutex_print(data->dt[phil_num] - data->live_time, phil_num,
						"is eating");
		ft_usleep(data->eat_time);
		fork_action(RELEASE_FORK, data, phil_num);
		(data->eaten[phil_num])++;
		if (somebody_dead(data))
			return (NULL);
		mutex_print(ft_time() - data->pthread_start[phil_num], phil_num,
					"is sleeping");
		if (somebody_dead(data))
			return (NULL);
		mutex_print(ft_time() - data->pthread_start[phil_num], phil_num,
					"is thinking");
	}
	return (NULL);
}

void	*death(t_data *data)
{
	uint	cnt;
	uint	eat_cnt;

	cnt = 0;
	eat_cnt = 0;
	while (!somebody_dead(data) && eat_cnt < data->eat_num)
	{
		cnt_eat += data->eaten[cnt] >= data->eat_num;
		if (data->eaten[cnt] >= data->eat_num && ++cnt)
			continue;
		if (ft_time() - data->pthread_start[cnt] > data->dt[cnt])
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->stop = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			mutex_print(ft_time() - data->pthread_start[cnt], cnt, "died");
			return (NULL);
		}
		cnt++;
	}
	return (NULL);
}

void	mutex_print(uintmax_t time, uint phil_num, char *str)
{
	static pthread_mutex_t	out_mutex = PTHREAD_MUTEX_INITIALIZER;
	static char				pattern = "[0000.000]:000000000 ";

	pthread_mutex_lock(&out_mutex);
	ft_putunbr(pattern + 1, (uint)time);
	ft_putunbr(pattern + 12, phil_num + 1);
	(void)write(1, pattern, 22);
	(void)write(1, str, ft_strlen(str));
	(void)write(1, "/n", 1);
	pthread_mutex_unlock(&out_mutex);
}

