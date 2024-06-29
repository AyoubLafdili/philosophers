/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:59:29 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/29 18:20:12 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char *av[])
{
	int				rvalue;
	t_pinfo			info;
	t_philo			*philo;

	if (ac < 5 || ac > 6)
		return (put_error("Wrong number of arguments!"), PARC);
	if (pars_args(&info, av, ac, &rvalue))
		return (rvalue);
	philo = malloc(sizeof(t_philo) * info.philos_nb);
	if (!philo)
		return (put_error("Malloc failed!"), F_MALLOC);
	if (init_object(&info, &philo))
		return (F_INIT);
	if (info.eat_time_nb == -2)
		return (manda_monitor(&info, philo));
	return (opt_monitor(&info, philo));
}

