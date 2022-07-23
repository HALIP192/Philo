/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:08:17 by ntitan            #+#    #+#             */
/*   Updated: 2022/07/23 21:34:09 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

t_data	*init_struct(void)
{
	t_data static	data;

	return (&data);
}

int	is_parse_done(int argc, char **argv, t_data *data)
{
	data->phil_num = ft_atoi(argv[1]);
	data->all_take_fork = 0;
	data->stop = 0;
	data->live_time = ft_atoi(argv[2]) * 1000;
	data->eat_time = ft_atoi(argv[3]) * 1000;
	data->sleep_time = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
	{
		data->all_args = 1;
		data->eat_num = ft_atoi(argv[5]);
		if ((int)data->phil_num <= 0 || (int)data->eat_time <= 0
			|| (int)data->sleep_time <= 0)
			return (1);
		else
			return (0);
	}
	data->all_args = 0;
	data->eat_num = 0;
	if (((int)data->phil_num <= 0 || (int)data->eat_time <= 0
			|| (int)data->sleep_time <= 0))
		return (1);
	return (0);
}

int	go_za_loop(uint start, t_data *data)
{
	int	pthread_error;

	pthread_error = 0;
	while (start < data->phil_num)
	{
		pthread_error |= pthread_create(data->pthreads + start, NULL,
				(void *(*)(void *))pthread_loop, (void *)(uintptr_t)start);
		ft_usleep(50);
		start += 2;
	}
	pthread_mutex_lock(&data->even_mutex);
	data->all_take_fork = 1;
	pthread_mutex_unlock(&data->even_mutex);
	return (pthread_error);
}

int	start_philo(t_data *data)
{
	int	i;
	int	mutex_error;

	if (malloc_data(data))
		return (-1);
	memset(data->eaten, 0x00, data->phil_num * sizeof(uint));
	i = 0;
	mutex_error = pthread_mutex_init(&data->dead_mutex, NULL);
	mutex_error |= pthread_mutex_init(&data->even_mutex, NULL);
	mutex_error |= big_mutex_init(data);
	mutex_error |= go_za_loop(1, data);
	while (!check_ready(data))
		;
	mutex_error |= go_za_loop(0, data);
	mutex_error |= pthread_create(data->pthreads + data->phil_num, NULL,
			(void *(*)(void *))death, data);
	return (mutex_error);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		error;

	data = init_struct();
	if ((argc != 5 && argc != 6) || is_parse_done(argc, argv, data))
		error_msg("ERROR: bad parametr passed.\n");
	error = start_philo(data);
	if (error == -1)
		error_msg("ERROR: some shit happendi with malloc.\n");
	end_philo(data);
	if (error)
		error_msg("ERROR: some unexpected shit happend.\n");
	return (0);
}
