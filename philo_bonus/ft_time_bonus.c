/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:06:32 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/30 21:50:53 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + (current_time.tv_usec / 1000));
}

void	ft_sleep(time_t amount)
{
	time_t	start;

	start = get_time();
	while (get_time() - start < amount)
		usleep(500);
}
