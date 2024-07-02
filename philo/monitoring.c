/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 14:48:45 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/02 15:39:44 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_died(t_philo *philos, int index)
{
	int	time_to_die;

	time_to_die = philos[0].initial_info->die_time;
	pthread_mutex_lock(philos[index].p_meal);
	if (get_time() - philos[index].last_meal >= time_to_die)
	{
		pthread_mutex_unlock(philos[index].p_meal);
		return (0);
	}
	pthread_mutex_unlock(philos[index].p_meal);
	return (1);
}

int	check_max_meals(t_philo *philos)
{
	int	i;
	int	max;

	i = 0;
	max = philos[0].initial_info->eat_time_nb;
	while (i < philos[0].initial_info->philos_nb)
	{
		pthread_mutex_lock(philos[i].p_meal);
		if (philos[i].meals_nb != max)
		{
			pthread_mutex_unlock(philos[i].p_meal);
			return (1);
		}
		pthread_mutex_unlock(philos[i].p_meal);
		i++;
	}
	return (0);
}

int	opt_monitor(t_ginfo *info, t_philo *philos, pthread_mutex_t *forks)
{
	int		i;
	int		rvalue;
	time_t	time_stamp;

	i = 0;
	info->start = get_time();
	ft_update_flag(info, 0);
	ft_sleep(info, 60);
	while (i < info->philos_nb)
	{
		rvalue = check_max_meals(philos);
		if (rvalue == 0 || !is_died(philos, i))
		{
			ft_update_flag(info, -1);
			if (rvalue != 0)
			{
				time_stamp = get_time() - info->start;
				printf("%ld\t%d\tis died\n", time_stamp, philos[i].order);
			}
			return (ft_clean(info, philos), free(forks), 0);
		}
		i = (i + 1) % info->philos_nb;
	}
	return (0);
}

int	manda_monitor(t_ginfo *info, t_philo *philos, pthread_mutex_t *forks)
{
	int		i;
	time_t	time_stamp;

	i = 0;
	info->start = get_time();
	ft_update_flag(info, 0);
	ft_sleep(info, 60);
	while (i < info->philos_nb)
	{
		if (!is_died(philos, i))
		{
			ft_update_flag(info, -1);
			time_stamp = get_time() - info->start;
			printf("%ld\t%d\tis died\n", time_stamp, philos[i].order);
			return (ft_clean(info, philos), free(forks), 0);
		}
		i = (i + 1) % info->philos_nb;
	}
	return (0);
}

int	monitoring(t_ginfo *info, t_philo *philos, pthread_mutex_t *forks)
{
	if (info->eat_time_nb == -2)
		return (manda_monitor(info, philos, forks));
	return (opt_monitor(info, philos, forks));
}
