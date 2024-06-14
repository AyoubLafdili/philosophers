/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_init_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:25:05 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/14 20:39:23 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int semaphore_init(t_pinfo *info)
{
	info->forks = sem_open("/forks", O_CREAT, 0666, info->philos_nb);
	if (info->forks == SEM_FAILED)
		return (1);
	// info->s_died = sem_open("/flag", O_CREAT, 0666, 1);
	// if (info->s_died == SEM_FAILED)
	// 	return (1);
	// info->s_meal = sem_open("/meal", O_CREAT, 0666, 1);
	// if (info->s_meal == SEM_FAILED)
	// 	return (1);
	// info->s_start = sem_open("/start", O_CREAT, 0666, 1);
	// if (info->s_start == SEM_FAILED)
	// 	return (1);
	return (0);
}

int init_object(t_pinfo *info, t_philo **philo)
{
	int i;

	i = 0;
	if (semaphore_init(info))
		return (put_error("Cannot open/create forks semaphore"), 1);
	info->start = get_time();
	while (i < info->philos_nb)
	{
		(*philo)[i].order = i + 1;
		(*philo)[i].meals_nb = 0;
		(*philo)[i].shared_info = info;
		(*philo)[i].pid = fork();
		if ((*philo)[i].pid == -1)
			exit(1);
		else if ((*philo)[i].pid == 0)
			child_func(&(*philo)[i]);
		i++;
	}

	return (0);
}
