/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:14:51 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/06 15:05:27 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t get_time()
{
	struct timeval current_time;
	
	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + (current_time.tv_usec / 1000));
}

void ft_sleep(time_t amount)
{
	time_t	start;	

	start = get_time();
	while (get_time() - start < amount)
		;
}

int	main(int ac, char *av[])
{
	int counter;
	t_pinfo	*info;
	pthread_mutex_t *forks;
	t_philo *philos;

	counter = 0;
	if (ac < 5 || ac > 6)
		return (write(2, "Wrong number of arguments!\n", 28), 1);
	info = malloc(sizeof(t_pinfo));
	if (!info)
		return (write(2, "malloc failed!\n", 16), 3);
	if (pars_args(&info, av, ac))
		return (write(2, "Invalid args!\n", 15), 2);
	forks = malloc(sizeof(pthread_mutex_t) * info->philos_nb);
	if (!forks)
		return (free(info), write(2, "malloc failed!\n", 16), 3);
	philos = malloc(sizeof(t_philo) * info->philos_nb);
	if (!philos)
		return (free(info), free(forks), write(2, "malloc failed!\n", 16), 3);
	if (forks_init(info, &forks) == -1)
		return (free(info), free(philos), free(forks), 4);
	if (philos_init(&info, &philos, &forks) == -1)
	{
		while (counter < info->philos_nb)
			pthread_mutex_destroy(&forks[counter++]);
		return (free(info), free(forks), free(philos), 5);
	}
	pthread_mutex_lock(&info->_start);
	info->start = get_time();
	pthread_mutex_unlock(&info->_start);
	pthread_mutex_lock(&info->_flag);
	info->flag = 0;
	pthread_mutex_unlock(&info->_flag);

	counter = 0;
	ft_sleep(100);
	while (counter < info->philos_nb)
	{
		pthread_mutex_lock(philos[counter].p_meal);
		if (get_time() - philos[counter].last_meal >= info->die_time)
		{
			
			pthread_mutex_lock(&info->_flag);
			info->flag = -1;
			pthread_mutex_unlock(&info->_flag);
			printf("%ld\t%d\tis died\n", get_time() - info->start, philos[counter].order);
			pthread_mutex_unlock(philos[counter].p_meal);
			counter = 0;
			while (counter < info->philos_nb)
			{
				pthread_join(philos[counter].id, NULL);
				counter++;				
			}
			return (free(forks), free(philos), 0);
		}
		pthread_mutex_unlock(philos[counter].p_meal);
		counter = (counter + 1) % info->philos_nb;
	}
	return (0);
}
