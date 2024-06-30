/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:08:23 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/30 22:22:05 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	before_exit(t_philo *philo, char *msg)
{
	sem_wait(philo->shared_info->sem.s_print);
	if (!msg)
		printf("%ld\t%d\t%s\n", get_timestamp(*philo), philo->order, DIED);
	else
		put_error(msg, 0);
	sem_post(philo->shared_info->sem.s_died);
	sem_close(philo->shared_info->sem.s_died);
	sem_close(philo->shared_info->sem.s_meals_nb);
	sem_close(philo->s_meal);
}

time_t	get_last_meal(t_philo *philo)
{
	time_t	timestamp;

	sem_wait(philo->s_meal);
	timestamp = get_time() - philo->last_meal;
	sem_post(philo->s_meal);
	return (timestamp);
}

time_t	get_timestamp(t_philo philo)
{
	return (get_time() - philo.shared_info->start);
}

void	put_error(char *msg, char flag)
{
	int	i;

	i = 0;
	while (msg[i])
		i++;
	if (flag > 0)
		write(2, msg, i);
	else
	{
		printf("DONE\n");
		write(2, READ, 5);
		write(2, msg, i);
		write(2, END, 4);
	}
	write(2, "\n", 1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
