/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:15:52 by ntitan            #+#    #+#             */
/*   Updated: 2022/07/10 21:04:42 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>

typedef struct s_data
{
	uint			phil_num;
	uint			live_time;
	uint			eat_time;
	uint			sleep_time;
	uint			eat_num;

	pthread_t		*pthreads;
	pthread_mutex_t	*mutex_s;
	uintmax_t		*pthread_start;
	uint			*eaten;
	uintmax_t		*death_time;

	pthread_mutex_t	dead_mutex;
	unsigned char	stop;

	pthread_mutex_t	even_eat;
	unsigned char	odd_ready;

}t_data;

void	error_msg(char *msg)
int		ft_strlen(char *str);
int		malloc_data(t_data *data);
void	ft_free(t_data *data);

#endif
