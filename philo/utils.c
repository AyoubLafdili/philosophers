/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 23:36:39 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/01 21:35:00 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_clean(t_ginfo *info, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < info->philos_nb)
	{
		pthread_join(philos[i].tid, NULL);
		pthread_mutex_destroy(philos[i].own_fork);
		i++;
	}
	pthread_mutex_destroy(&info->_flag);
	pthread_mutex_destroy(&info->_start);
	pthread_mutex_destroy(&info->_meal);
	free(info);
	free(philos);
}

void	put_error(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
		i++;
	write(2, READ, 6);
	write(2, msg, i);
	write(2, END, 5);
	write(2, "\n", 1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	ft_update_flag(t_ginfo *info, int set_val)
{
	pthread_mutex_lock(&info->_flag);
	info->flag = set_val;
	pthread_mutex_unlock(&info->_flag);
}

int	check_flag(t_ginfo *info)
{
	int	rvalue;

	pthread_mutex_lock(&info->_flag);
	rvalue = info->flag;
	pthread_mutex_unlock(&info->_flag);
	return (rvalue);
}
