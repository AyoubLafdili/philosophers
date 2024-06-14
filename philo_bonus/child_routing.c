/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:25:18 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/14 20:44:01 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_print(t_philo *philo, char *msg)
{
	int order;

	order = philo->order;
	// sem_wait(philo->shared_info->s_start);
	if (*(philo->died) != -1)
	{
		printf("%ld\t%d\t%s\n", get_time() - philo->shared_info->start, order, msg);
		return (0);
	}
	return (1);
	// sem_post(philo->shared_info->s_start);
}

int	eat(t_philo *philo)
{
	printf(""READ"hello10"END"\n");
	sem_wait(philo->shared_info->forks);
	if (ft_print(philo, TOOK))
		return (sem_post(philo->shared_info->forks), 1);
	sem_wait(philo->shared_info->forks);
	if (ft_print(philo, TOOK))
		return (sem_post(philo->shared_info->forks),
			sem_post(philo->shared_info->forks), 1);
	if (ft_print(philo, EAT))
		return (sem_post(philo->shared_info->forks),
			sem_post(philo->shared_info->forks), 1);
	philo->meals_nb++;
	philo->last_meal = get_time();
	ft_sleep(philo->shared_info->eat_time);
	sem_post(philo->shared_info->forks);
	sem_post(philo->shared_info->forks);
	return (0);
}

int sleeping(t_philo *philo)
{
	if (ft_print(philo, SLEEP))
		return (1);
	ft_sleep(philo->shared_info->sleep_time);
	if (ft_print(philo, THINK))
		return (1);
	return (0);
}

void *child_routing(void *param)
{
	
	t_philo *philo;
	philo = param;
	while (1)
	{
		if (eat(philo))
		{
			
			printf("hello1\n");
			return (NULL);
		}
		if (sleeping(philo))
		{
			printf("hello\n");
			return (NULL);
		}
	}
	return (NULL);
}

int	child_func(t_philo *philo)
{
	pthread_t id;
	int		*flag;

	flag = malloc(sizeof(int));
	if (!flag)
		exit (1);
	memset(flag, 0, sizeof(int));
	philo->died = flag;
	if (philo->order % 2 == 0)
		ft_sleep(philo->shared_info->eat_time);
	philo->last_meal = get_time();
	pthread_create(&id, NULL, child_routing, philo);
	usleep(100);
	while (1)
	{
		time_t lastmeal = philo->last_meal;
		time_t current = get_time();
		// printf("philo = %d\t\ttimecheck = %ld\n", philo->order, current - lastmeal);
		// printf("last = %ld\t\tcurrent = %ld\n", lastmeal, current);
		if (current - lastmeal >= philo->shared_info->die_time)
		{
			*(philo->died) = -1;
			// ft_print(philo, DIED);
			// printf("died value %d\n", *flag);
			if (sem_close(philo->shared_info->forks))
				write(2, "sem_close fail\n", 16);
			// sem_unlink("\forks");
			// sem_close(philo->shared_info->s_start);
			exit(philo->order);
		}
	}
}