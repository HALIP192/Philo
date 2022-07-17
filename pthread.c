/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:36:31 by ntitan            #+#    #+#             */
/*   Updated: 2022/07/16 17:17:51 by ntitan           ###   ########.fr       */
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

	if (action == 1)
	{
		pthread_mutex_lock(data->mutex_s + phil_num);
		if (data->phil_num == 1)
		{
			mutex_print(ft_time() - data->pthread_start[phil_num], phil_num,
						"has taken L fork", data);
			ft_usleep(data->live_time + 100);
			return (0);
		}
		mutex_print(ft_time() - data->pthread_start[phil_num], phil_num,
							"has taken L fork", data);
		pthread_mutex_lock(data->mutex_s + (phil_num + 1) % data->phil_num);
		time = ft_time() - data->pthread_start[phil_num];
		mutex_print(time, phil_num, "has taken R fork", data);
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
	t_data		*data;
	uintmax_t	delay;

	data = init_struct();
	data->pthread_start[phil_num] = ft_time();
	data->death_time[phil_num] = data->live_time;
	while (((data->eaten[phil_num] < data->eat_num && data->all_args)
			|| (!data->all_args))  && !somebody_dead(data))
	{
		delay = fork_action(TAKE_FORK, data, phil_num);
		data->death_time[phil_num] = delay + data->live_time;
		mutex_print(ft_time() - data->pthread_start[phil_num], phil_num,
					"is eating", data);
		ft_usleep(data->eat_time);
		fork_action(RELEASE_FORK, data, phil_num);
		data->eaten[phil_num] += 1;
		mutex_print(ft_time() - data->pthread_start[phil_num], phil_num,
					"is sleeping", data);
		ft_usleep(data->sleep_time);
		mutex_print(ft_time() - data->pthread_start[phil_num], phil_num,
					"is thinking",data);
		//ft_usleep(data->sleep_time);
	}
	return (NULL);
}

void	*death(t_data *data)
{
	uint	cnt;
	uint	eat_cnt;

	eat_cnt = 0;
	while (!somebody_dead(data) && (eat_cnt < data->phil_num || !data->all_args) )
	{
		cnt = 0;
		eat_cnt = 0;
		while (cnt < data->phil_num && !somebody_dead(data))
		{
			eat_cnt += data->eaten[cnt] >= data->eat_num;
			if (((data->eaten[cnt] >= data->eat_num && data->all_args)
			|| (data->eaten[cnt] && !data->all_args))&& ++cnt )
				continue;
			if (ft_time() - data->pthread_start[cnt] > data->death_time[cnt]) {
				pthread_mutex_lock(&data->dead_mutex);
				data->stop = 1;
				pthread_mutex_unlock(&data->dead_mutex);
				mutex_print(ft_time() - data->pthread_start[cnt], cnt, "died", data);
				return (NULL);
			}
			cnt++;
		}
	}
	//write(1, "----------:", 11);
	return (NULL);
}

void	mutex_print(uintmax_t time, uint phil_num, char *str, t_data *data)
{
	static pthread_mutex_t	out_mutex = PTHREAD_MUTEX_INITIALIZER;
	static char				pattern[] = "[00000.000]:000000000 ";

	if (somebody_dead(data) && (str[0] != 'd'))
		return ;
	pthread_mutex_lock(&out_mutex);
	ft_putunbr(pattern + 1, (uint)time);
	ft_putunbr(pattern + 12, phil_num + 1);
	(void)write(1, pattern, 22);
	(void)write(1, str, ft_strlen(str));
	(void)write(1, "\n", 1);
	//printf("%ju  %d %s\n", (uintmax_t)time,phil_num, str);
	pthread_mutex_unlock(&out_mutex);
}

