/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_init_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:25:05 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/29 17:59:55 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	semaphore_init(t_pinfo *info)
{
	sem_unlink("/forks");
	sem_unlink("/died");
	sem_unlink("/print");
	sem_unlink("/meals_nb");
	info->sem.forks = sem_open("/forks", O_CREAT, 0666, info->philos_nb);
	if (info->sem.forks == SEM_FAILED)
		return (1);
	info->sem.s_died = sem_open("/died", O_CREAT, 0666, 0);
	if (info->sem.s_died == SEM_FAILED)
		return (clean_semaphores(info, 1));
	info->sem.s_print = sem_open("/print", O_CREAT, 0666, 1);
	if (info->sem.s_print == SEM_FAILED)
		return (clean_semaphores(info, 2));	
	info->sem.s_meals_nb = sem_open("/meals_nb", O_CREAT, 0666, 0);
	if (info->sem.s_meals_nb == SEM_FAILED)
		return (clean_semaphores(info, 3));
	info->sem.s_race = sem_open("/race", O_CREAT, 0666, 1);
	if (info->sem.s_race == SEM_FAILED)
		return (clean_semaphores(info, 4));
	return (NO_ERR);
}

int init_object(t_pinfo *info, t_philo **philo)
{
	int i;

	i = 0;
	if (semaphore_init(info))
		return (free(info->flag), put_error("Cannot open/create forks semaphore"), 1);
	info->start = get_time();
	while (i < info->philos_nb)
	{
		(*philo)[i].order = i + 1;
		(*philo)[i].meals_nb = 0;
		(*philo)[i].shared_info = info;
		(*philo)[i].died = 0;
		(*philo)[i].pid = fork();
		if ((*philo)[i].pid == -1)
			return (put_error("fork() unable to spawn!"), clean_up(*philo, i), 1);
		else if ((*philo)[i].pid == 0)
			child_func(&(*philo)[i]);
		i++;
	}
	return (NO_ERR);
}
