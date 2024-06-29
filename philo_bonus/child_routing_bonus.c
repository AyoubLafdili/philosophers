/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_routing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:25:18 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/29 22:32:30 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_print(t_philo *philo, char *msg)
{
	int order;

	order = philo->order;
	sem_wait(philo->shared_info->sem.s_print);
		printf("%ld\t%d\t%s\n", get_timestamp(*philo), order, msg);
	sem_post(philo->shared_info->sem.s_print);
}

int	eat(t_philo *philo)
{
	// printf("befor first fork philo order %d\n", philo->order);
	sem_wait(philo->shared_info->sem.forks);
	// printf("after first fork philo order %d\n", philo->order);
	ft_print(philo, TOOK);
	if (philo->shared_info->philos_nb == 1)
		return (1);
	sem_wait(philo->shared_info->sem.forks);
	ft_print(philo, TOOK);
	ft_print(philo, EAT);
	sem_wait(philo->s_meal);
	sem_post(philo->shared_info->sem.s_meals_nb);
	philo->last_meal = get_time();
	sem_post(philo->s_meal);
	ft_sleep(philo->shared_info->eat_time);
	sem_post(philo->shared_info->sem.forks);
	sem_post(philo->shared_info->sem.forks);
	return (0);
}


void before_exit(t_philo *philo, char *msg)
{
	sem_wait(philo->shared_info->sem.s_print);
	if (!msg)
		printf("%ld\t%d\t%s\n", get_timestamp(*philo), philo->order, DIED);
	else
		put_error(msg);
	sem_post(philo->shared_info->sem.s_died);
	sem_close(philo->shared_info->sem.s_died);
	sem_close(philo->shared_info->sem.s_meals_nb);
	sem_close(philo->s_meal);
}

void *child_routing(void *param)
{
	t_philo *philo;
	
	philo = (t_philo *)param;
	while (1)
	{
		if (eat(philo))
			return (NULL);
		ft_print(philo, SLEEP);
		ft_sleep(philo->shared_info->sleep_time);
		ft_print(philo, THINK);
	}
	return (NULL);
}

void child_sem_thread_init(t_philo *philo, char *sem_name)
{
	name_semaphore(sem_name, "/meal", philo->order);
	sem_unlink(sem_name);
	philo->s_meal = sem_open(sem_name, O_CREAT, 0666, 1);
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
	char		sem_name[10];
	if (philo->order % 2 == 0)
		ft_sleep(philo->shared_info->eat_time);
	philo->last_meal = get_time();
	child_sem_thread_init(philo, sem_name);
	while (1)
	{
		if (get_last_meal(philo) >= philo->shared_info->die_time)
		{
			before_exit(philo, NULL);
			sem_unlink(sem_name);
			exit (NO_ERR);
		}
		usleep(300);
	}
}
