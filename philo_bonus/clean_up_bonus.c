/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 08:50:55 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/30 22:25:28 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_sem_names(t_philo *philo, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		free(philo[i].sem_name);
		i++;
	}
}

void	sem_subclean(sem_t *sem, char *sem_name)
{
	sem_close(sem);
	sem_unlink(sem_name);
}

int	clean_semaphores(t_pinfo *info, int order)
{
	if (order == 1)
		return (sem_subclean(info->sem.forks, "/forks"), 1);
	else if (order == 2)
		return (sem_subclean(info->sem.s_died, "/died"),
			clean_semaphores(info, order - 1), 1);
	else if (order == 3)
		return (sem_subclean(info->sem.s_print, "/print"),
			clean_semaphores(info, order - 1), 1);
	else if (order == 4)
		return (sem_subclean(info->sem.s_meals_nb, "/meals_nb"),
			clean_semaphores(info, order - 1), 1);
	else if (order == 5)
		return (sem_subclean(info->sem.s_race, "/race"),
			clean_semaphores(info, order - 1), 1);
	return (0);
}

int	clean_up(t_philo *philo, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{
		kill(philo[i].pid, SIGKILL);
		sem_unlink(philo[i].sem_name);
		i++;
	}
	i = 0;
	while (waitpid(-1, NULL, 0) != -1)
		;
	clean_semaphores(philo[0].shared_info, 5);
	free_sem_names(philo, philo->shared_info->ph_nb);
	free(philo->shared_info->flag);
	free(philo);
	return (0);
}
