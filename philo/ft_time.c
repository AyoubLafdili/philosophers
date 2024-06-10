/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 23:01:01 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/10 10:57:50 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + (current_time.tv_usec / 1000));
}

void	ft_sleep(t_pinfo *data, time_t amount)
{
	time_t	start;

	start = get_time();
	while (get_time() - start < amount)
	{
		if (check_flag(data) == -1)
			break ;
		usleep(100);
	}
}
