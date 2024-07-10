/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 12:30:23 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/07 14:48:56 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_print(t_philo *param, char *msg)
{
	time_t	time_stamp;

	pthread_mutex_lock(param->p_flag);
	if (param->initial_info->flag != -1)
	{
		pthread_mutex_lock(param->p_start);
		time_stamp = get_time() - param->initial_info->start;
		pthread_mutex_unlock(param->p_start);
		printf("%ld %d %s\n", time_stamp, param->order, msg);
		pthread_mutex_unlock(param->p_flag);
		return (0);
	}
	pthread_mutex_unlock(param->p_flag);
	return (1);
}

int	ft_pause(t_philo *philo)
{
	while (1)
	{
		if (check_flag(philo->initial_info) == -1)
			return (1);
		if (check_flag(philo->initial_info) == 0)
			break ;
	}
	pthread_mutex_lock(philo->p_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->p_meal);
	return (0);
}

int	sleeping(t_philo *philo)
{
	if (ft_print(philo, "is sleeping"))
		return (1);
	ft_sleep(philo->initial_info, philo->initial_info->sleep_time);
	if (ft_print(philo, "is thinking"))
		return (1);
	return (0);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->own_fork);
	if (ft_print(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->own_fork), 1);
	if (philo->initial_info->philos_nb == 1)
		return (pthread_mutex_unlock(philo->own_fork), 1);
	pthread_mutex_lock(philo->right_fork);
	if (ft_print(philo, "has taken a fork"))
		return (pthread_mutex_unlock(philo->own_fork),
			pthread_mutex_unlock(philo->right_fork), 1);
	if (ft_print(philo, "is eating"))
		return (pthread_mutex_unlock(philo->own_fork),
			pthread_mutex_unlock(philo->right_fork), 1);
	pthread_mutex_lock(philo->p_meal);
	philo->meals_nb++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->p_meal);
	ft_sleep(philo->initial_info, philo->initial_info->eat_time);
	pthread_mutex_unlock(philo->own_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	*thread_func(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	if (ft_pause(philo))
		return (NULL);
	if (philo->order % 2 == 0)
		ft_sleep(philo->initial_info, philo->initial_info->eat_time);
	while (1)
	{
		if (philo->initial_info->eat_time_nb != -2
			&& philo->meals_nb == philo->initial_info->eat_time_nb)
			return (NULL);
		if (eat(philo))
			return (NULL);
		if (sleeping(philo))
			return (NULL);
	}
	return (NULL);
}
