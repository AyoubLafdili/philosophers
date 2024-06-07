/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:30:23 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/07 20:26:27 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_print(t_philo *param, char *msg)
{
	pthread_mutex_lock(param->p_flag);
	if (param->initial_info->flag != -1)
	{
		pthread_mutex_lock(param->p_start);
		printf("%ld\t%d\t%s\n", get_time() - param->initial_info->start, param->order, msg);
		pthread_mutex_unlock(param->p_start);
		pthread_mutex_unlock(param->p_flag);
		return (0);
	}
	else
		pthread_mutex_unlock(param->p_flag);
	return (1);
}

void ft_pause(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(philo->p_flag);
		if (philo->initial_info->flag == 0)
		{
			pthread_mutex_unlock(philo->p_flag);
			break ;
		}
		pthread_mutex_unlock(philo->p_flag);
	}
	pthread_mutex_lock(philo->p_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->p_meal);
}

int sleeping(t_philo *philo)
{
	if (ft_print(philo, "is sleeping"))
		return (1);
	ft_sleep(philo->initial_info, philo->initial_info->sleep_time);
	if (ft_print(philo, "is thinking"))
		return (1);
	return (0);
}

int eat(t_philo *philo)
{
	pthread_mutex_lock(philo->own_fork);
	if (ft_print(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->own_fork), 1);
	if (philo->initial_info->philos_nb == 1)
		return (pthread_mutex_unlock(philo->own_fork), 1);
	pthread_mutex_lock(philo->right_fork);
	if (ft_print(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(philo->own_fork);
		return (pthread_mutex_unlock(philo->right_fork), 1);
	}
	if (ft_print(philo, "is eating"))
	{
		pthread_mutex_unlock(philo->own_fork);
		return (pthread_mutex_unlock(philo->right_fork), 1);
	}
	ft_sleep(philo->initial_info, philo->initial_info->eat_time);
	pthread_mutex_lock(philo->p_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->p_meal);
	pthread_mutex_unlock(philo->own_fork);
	return (pthread_mutex_unlock(philo->right_fork), 0);
}

void *thread_func(void *param)
{
	t_philo *philo;
	
	philo = (t_philo *) param;
	ft_pause(philo);
	if (philo->order % 2 == 0)
		ft_sleep(philo->initial_info, philo->initial_info->eat_time);
	while (1)
	{
		if (eat(philo))
			return (NULL);
		if (sleeping(philo))
			return (NULL);
	}
	return (NULL);
}
