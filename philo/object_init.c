/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:28:46 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/07 20:12:45 by alafdili         ###   ########.fr       */
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
			return (write(2, "mutex_init failed!", 19), -1);
		}
		i++;
	}
	return (0);
}

int philos_init(t_pinfo **info, t_philo **philos, pthread_mutex_t **forks)
{
	int i;

	i = 0;
	pthread_mutex_init(&(*info)->_flag, NULL);
	pthread_mutex_init(&(*info)->_start, NULL);
	pthread_mutex_init(&(*info)->meal, NULL);
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
			return (write(2, "pthread_create failed!\n", 24), -1);
		i++;
	}
	return (0);
}