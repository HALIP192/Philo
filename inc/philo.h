/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntitan <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 13:15:52 by ntitan            #+#    #+#             */
/*   Updated: 2022/07/16 15:47:11 by ntitan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


# define uint unsigned int


typedef struct s_data
{
	uint					phil_num;
	uint					live_time;
	uint					eat_time;
	uint					sleep_time;
	uint					eat_num;

	pthread_t				*pthreads;
	pthread_mutex_t			*mutex_s;
	uintmax_t				*pthread_start;
	uint					*eaten;
	uintmax_t				*death_time;

	pthread_mutex_t			dead_mutex;
	unsigned char			stop;
	
	volatile sig_atomic_t	all_take_fork;

}t_data;

void		error_msg(char *msg);
int			ft_strlen(char *str);
int			malloc_data(t_data *data);
void		ft_free(t_data *data);
int			somebode_dead(t_data *data);
void		ft_putnbr(char *dest, uint src);
uintmax_t	ft_time(void);
void		*pthread_loop(size_t phil_num);
void		*death(t_data *data);
void		mutex_print(uintmax_t time, uint phil_num, char *str);
int			ft_atoi(const char *str);
void		end_philo(t_data *data);
void		ft_usleep(useconds_t usec);
t_data		*init_struct(void);
#endif
