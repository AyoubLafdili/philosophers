/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:28:46 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/10 10:56:27 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks_init(t_pinfo *info, pthread_mutex_t **to_init)
{
	int	i;
	int	j;

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

int	ft_init_mutex(t_pinfo **info)
{
	if (pthread_mutex_init(&(*info)->_flag, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(*info)->_start, NULL))
	{
		pthread_mutex_destroy(&(*info)->_flag);
		return (-1);
	}
	if (pthread_mutex_init(&(*info)->meal, NULL))
	{
		pthread_mutex_destroy(&(*info)->_flag);
		pthread_mutex_destroy(&(*info)->_start);
		return (-1);
	}
	return (0);
}

/**
 * @brief 
 * 
 * @param info shared data stracutre between philos
 * @param philos data structure for each philo
 * @param forks struct of mutexes that represent the forks of philos
 * @return -2 on succes, -1 failure of mutix_init, [0, philo_nb] failure
 * of phtread_create, used to indicate which index i need to join.
 */

int	philos_init(t_pinfo **info, t_philo **philos, pthread_mutex_t **forks)
{
	int	i;
	int	c;

	i = 0;
	if (ft_init_mutex(info) == -1)
		return (-1);
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
		c = pthread_create(&(*philos)[i].tid, NULL, thread_func, &(*philos)[i]);
		if (c != 0)
			return (put_error("Pthread_create failed!"), i);
		i++;
	}
	return (-2);
}

void	thread_termination(t_pinfo **info, t_philo **philos, int threads)
{
	int	i;

	i = 0;
	ft_update_flag(*info, -1);
	while (i < threads)
	{
		pthread_join((*philos)[i].tid, NULL);
		i++;
	}
}

int	init_object(t_pinfo **info, t_philo **philos, pthread_mutex_t **forks)
{
	int	counter;
	int	rvalue;

	counter = 0;
	if (forks_init(*info, forks) == -1)
		return (free(*info), free(*philos), free(*forks), 4);
	rvalue = philos_init(info, philos, forks);
	if (rvalue != -2)
	{
		if (rvalue == -1)
		{
			put_error("mutex_init failed!");
			free(*info);
			return (free(*forks), free(*philos), 4);
		}
		thread_termination(info, philos, rvalue);
		pthread_mutex_destroy(&(*info)->_flag);
		pthread_mutex_destroy(&(*info)->_start);
		pthread_mutex_destroy(&(*info)->meal);
		while (counter < (*info)->philos_nb)
			pthread_mutex_destroy(&(*forks)[counter++]);
		return (free(*info), free(*forks), free(*philos), 5);
	}
	return (0);
}
