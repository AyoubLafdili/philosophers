/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:25:18 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/08 17:07:05 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print(t_philo *philo, char *msg)
{
	int	order;

	order = philo->order;
	sem_wait(philo->shared_info->sem.s_print);
	printf("%ld %d %s\n", get_timestamp(*philo), order, msg);
	sem_post(philo->shared_info->sem.s_print);
}

int	eat(t_philo *philo)
{
	sem_wait(philo->shared_info->sem.forks);
	ft_print(philo, FORKED);
	if (philo->shared_info->ph_nb == 1)
		return (FAILURE);
	sem_wait(philo->shared_info->sem.forks);
	ft_print(philo, FORKED);
	ft_print(philo, EAT);
	sem_wait(philo->s_meal);
	philo->last_meal = get_time();
	sem_post(philo->s_meal);
	ft_sleep(philo->shared_info->eat_time);
	sem_post(philo->shared_info->sem.forks);
	sem_post(philo->shared_info->sem.forks);
	return (SUCCES);
}

void	*child_routing(void *param)
{
	t_philo	*philo;
	int		meals_counter;

	meals_counter = 0;
	philo = (t_philo *)param;
	while (1)
	{
		if (philo->shared_info->eat_time_nb != -2
			&& meals_counter == philo->shared_info->eat_time_nb)
		{
			sem_post(philo->shared_info->sem.s_meals_nb);
			sem_close(philo->shared_info->sem.s_died);
			sem_close(philo->shared_info->sem.s_meals_nb);
			sem_close(philo->s_meal);
			exit(SUCCES);
		}
		if (eat(philo))
			return (NULL);
		ft_print(philo, SLEEP);
		ft_sleep(philo->shared_info->sleep_time);
		ft_print(philo, THINK);
		meals_counter++;
	}
	return (NULL);
}

void	child_sem_thread_init(t_philo *philo)
{
	sem_unlink(philo->sem_name);
	philo->s_meal = sem_open(philo->sem_name, O_CREAT, 0666, 1);
	if (philo->s_meal == SEM_FAILED)
	{
		before_exit(philo, "Cannot open/create child semaphore");
		exit(F_INIT);
	}
	if (pthread_create(&philo->id, NULL, child_routing, philo) != 0)
	{
		before_exit(philo, "Unable thread creation!");
		exit (F_CREATE_TH);
	}
	pthread_detach(philo->id);
}

int	child_func(t_philo *philo)
{
	if (philo->order % 2 == 0)
		ft_sleep(philo->shared_info->eat_time);
	philo->last_meal = get_time();
	child_sem_thread_init(philo);
	while (1)
	{
		if (get_last_meal(philo) >= philo->shared_info->die_time)
		{
			before_exit(philo, NULL);
			sem_unlink(philo->sem_name);
			exit (SUCCES);
		}
		usleep(100);
	}
}
