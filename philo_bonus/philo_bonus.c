/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:59:29 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/14 18:38:17 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int clean_up(t_pinfo *info, t_philo *philo, pid_t execluded)
{
	int i;

	i = 0;
	while (i < info->philos_nb)
	{
		if (philo[i].pid != execluded)
			kill(philo[i].pid, SIGKILL);
		i++;
	}
	sem_close(info->forks);
	sem_unlink("/forks");
	// sem_close(info->s_meal);
	// sem_close(info->s_start);
	// sem_close(info->s_died);
	// sem_unlink("/flag");
	// sem_unlink("/meal");
	// sem_unlink("/start");
	free(philo);
	return (0);
}

int manda_monitor(t_pinfo *info,  t_philo *philos)
{
	int i;
	int	status;
	int term_pid;

	i = 0;
	while (i < info->philos_nb)
	{
		term_pid = waitpid(philos[i].pid, &status, WNOHANG);
		if (term_pid == -1)
			return (free(philos), 0);
		else if (term_pid > 0)
		{
			printf("%ld\t%d\t%s\n", get_time() - info->start, status, DIED);
			return (clean_up(info, philos, term_pid), 0);
		}
		usleep(100);
		i = (i + 1) % info->philos_nb;
	}
	return (0);
}


int	main(int ac, char *av[])
{
	int				rvalue;
	t_pinfo			info;
	t_philo			*philo;

	if (ac < 5 || ac > 6)
		return (put_error("Wrong number of arguments!"), 1);
	if (pars_args(&info, av, ac, &rvalue))
		return (rvalue);
	philo = malloc(sizeof(t_philo) * info.philos_nb);
	if (!philo)
		return (put_error("Malloc failed!"), 2);
	if (init_object(&info, &philo))
		return (free(philo), 3);
	manda_monitor(&info, philo);
	return (0);
}
