/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:14:51 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/08 22:32:24 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_update_flag(t_pinfo *info, int set_val)
{
	pthread_mutex_lock(&info->_flag);
	info->flag = set_val;
	pthread_mutex_unlock(&info->_flag);
}
int is_done(t_philo *philos)
{
	int i;
	int max;

	i = 0;
	max = philos[0].initial_info->eat_time_nb;
	while(i < philos[0].initial_info->philos_nb)
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

int check_mels(t_philo *philos, int index)
{
	int time_to_die;

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

int monitor2_func(t_pinfo *info, t_philo *philos, pthread_mutex_t *forks)
{
	int i;
	int rvalue;

	i = 0;
	info->start_sim = get_time();
	ft_update_flag(info, 0);
	ft_sleep(info, 60);
	while (i < info->philos_nb)
	{
		if ((rvalue = is_done(philos)) == 0 || !check_mels(philos, i))
		{
			ft_update_flag(info, -1);
			if (rvalue != 0)
				printf("%ld\t%d\tis died\n", get_time() - info->start_sim, philos[i].order);
			return (ft_clean(info, philos), free(forks), 0);
		}
		i = (i + 1) % info->philos_nb;
	}
	return (0);
}

int monitor_func(t_pinfo *info, t_philo *philos, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	info->start_sim = get_time();
	ft_update_flag(info, 0);
	ft_sleep(info, 60);
	while (i < info->philos_nb)
	{
		if (!check_mels(philos, i))
		{
			ft_update_flag(info, -1);
			printf("%ld\t%d\tis died\n", get_time() - info->start_sim, philos[i].order);
			return (ft_clean(info, philos), free(forks), 0);
		}
		i = (i + 1) % info->philos_nb;
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_pinfo			*info;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				rvalue;

	if (ac < 5 || ac > 6)
		return (put_error("Wrong number of arguments!"), 1);
	info = malloc(sizeof(t_pinfo));
	if (!info)
		return (put_error("malloc failed!"), 3);
	if (pars_args(&info, av, ac, &rvalue))
		return (free(info), rvalue);
	forks = malloc(sizeof(pthread_mutex_t) * info->philos_nb);
	if (!forks)
		return (free(info), put_error("malloc failed!"), 3);
	philos = malloc(sizeof(t_philo) * info->philos_nb);
	if (!philos)
		return (free(info), free(forks), put_error("malloc failed!"), 3);
	if ((rvalue = init_object(&info, &philos, &forks)) != 0)
		return (rvalue);
	if (info->eat_time_nb == -1)
		return (monitor_func(info, philos, forks));
	return (monitor2_func(info, philos, forks));
}

