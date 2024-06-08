/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:28:46 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/08 17:57:39 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int forks_init(t_pinfo *info, pthread_mutex_t **to_init)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (i < info->philos_nb)
	{
		if (pthread_mutex_init(&to_init[0][i], NULL) != 0)
		{
			while (j < i)
			{
				pthread_mutex_destroy(&to_init[0][j]);
				j++;
			}
			return (put_error("mutex_init failed!"), -1);
		}
		i++;
	}
	return (0);
}

int philos_init(t_pinfo **info, t_philo **philos, pthread_mutex_t **forks)
{
	int i;

	i = 0;
	if (pthread_mutex_init(&(*info)->_flag, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(*info)->_start, NULL))
		return (pthread_mutex_destroy(&(*info)->_flag), -1);
	if (pthread_mutex_init(&(*info)->meal, NULL))
		return (pthread_mutex_destroy(&(*info)->_flag), 
	pthread_mutex_destroy(&(*info)->_start), -1);
	while (i < (*info)->philos_nb)
	{
		(*philos)[i].p_flag = &(*info)->_flag;
		(*philos)[i].p_start = &(*info)->_start;
		(*philos)[i].order = i + 1;
		(*philos)[i].meals_nb = 0;
		(*philos)[i].last_meal = 0;
		(*philos)[i].p_meal = &(*info)->meal;
		(*philos)[i].initial_info = *info;
		(*philos)[i].own_fork = &(*forks)[i];
		(*philos)[i].right_fork = &(*forks)[(i + 1) % (*info)->philos_nb];
		if (pthread_create(&(*philos)[i].id, NULL, thread_func, &(*philos)[i]) != 0)
			return (put_error("pthread_create failed!"), -2);
		i++;
	}
	return (0);
}

int init_object(t_pinfo **info, t_philo **philos, pthread_mutex_t **forks)
{
	int counter;
	int	rvalue;

	counter = 0;
	if (forks_init(*info, forks) == -1)
		return (free(*info), free(*philos), free(*forks), 4);
	rvalue = philos_init(info, philos, forks);
	if (rvalue == -1 || rvalue == -2)
	{
		if (rvalue == -1)
			put_error("mutex_init failed!");
		while (counter < (*info)->philos_nb)
			pthread_mutex_destroy(&(*forks)[counter++]);
		return (free(*info), free(*forks), free(*philos), 5);
	}
	return (0);
}