/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:37:44 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/30 22:25:28 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_flag(t_pinfo *info)
{
	int	status;

	sem_wait(info->sem.s_race);
	status = *info->flag;
	sem_post(info->sem.s_race);
	return (status);
}

void	*meals_monitor(void *param)
{
	int		total_meals;
	t_pinfo	*info;

	total_meals = 0;
	info = (t_pinfo *)param;
	while (check_flag(info) != 1)
	{
		if (total_meals == info->eat_time_nb * info->ph_nb)
		{
			sem_post(info->sem.s_died);
			break ;
		}
		sem_wait(info->sem.s_meals_nb);
		total_meals++;
	}
	return (NULL);
}

int	opt_monitor(t_pinfo *info, t_philo *philos)
{
	if (pthread_create(&info->monitor_id, NULL, meals_monitor, info) != 0)
		return (put_error("Unable thread creation!", 0),
			clean_up(philos, info->ph_nb), F_CREATE_TH);
	pthread_detach(info->monitor_id);
	sem_wait(info->sem.s_died);
	sem_wait(info->sem.s_race);
	*(info->flag) = 1;
	sem_post(info->sem.s_race);
	sem_post(info->sem.s_meals_nb);
	clean_up(philos, info->ph_nb);
	return (0);
}

int	manda_monitor(t_pinfo *info, t_philo *philos)
{
	sem_wait(info->sem.s_died);
	clean_up(philos, info->ph_nb);
	return (0);
}
