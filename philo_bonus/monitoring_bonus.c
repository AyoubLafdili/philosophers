/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 11:37:44 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/29 14:52:46 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *meals_monitor(void *param)
{
	int	total_meals;
	t_pinfo *info;

	total_meals = 0;
	info = (t_pinfo *)param;
	while (check_flag(info) != 1)
	{
		if (total_meals == info->eat_time_nb * info->philos_nb)
		{
			sem_wait(info->sem.s_print);
			sem_post(info->sem.s_died);
			break ;
		}
		sem_wait(info->sem.s_meals_nb);
		total_meals++;
	}
	return (NULL);
}

int opt_monitor(t_pinfo *info, t_philo *philos)
{
	if (pthread_create(&info->monitor_id, NULL, meals_monitor, info) != 0)
		return (put_error("Unable thread creation!"),
			clean_up(philos, info->philos_nb), F_CREATE_TH);
	pthread_detach(info->monitor_id);
	sem_wait(info->sem.s_died);
	sem_wait(info->sem.s_race);
	*(info->flag) = 1;
	sem_post(info->sem.s_race);
	sem_post(info->sem.s_meals_nb);
	clean_up(philos, info->philos_nb);
	return (0);
}

int manda_monitor(t_pinfo *info, t_philo *philos)
{
	sem_wait(info->sem.s_died);
	clean_up(philos, info->philos_nb);
	return (0);
}
