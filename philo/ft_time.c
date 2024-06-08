/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 23:01:01 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/07 23:01:31 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t get_time()
{
	struct timeval current_time;
	
	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + (current_time.tv_usec / 1000));
}

void ft_sleep(t_pinfo *data, time_t amount)
{
	time_t	start;

	start = get_time();
	while (get_time() - start < amount)
	{
		pthread_mutex_lock(&data->_flag);
		if (data->flag == -1)
		{
			pthread_mutex_unlock(&data->_flag);
			break ;
		}
		pthread_mutex_unlock(&data->_flag);
		usleep(100);
	}
}
