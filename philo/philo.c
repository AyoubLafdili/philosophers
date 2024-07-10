/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:14:51 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/07 10:47:44 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	int				rvalue;
	t_ginfo			*info;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (ac < 5 || ac > 6)
		return (put_error("Wrong number of arguments!"), 1);
	info = malloc(sizeof(t_ginfo));
	if (!info)
		return (put_error("Malloc failed!"), 3);
	if (pars_args(&info, av, ac, &rvalue))
		return (free(info), rvalue);
	forks = malloc(sizeof(pthread_mutex_t) * info->philos_nb);
	if (!forks)
		return (free(info), put_error("Malloc failed!"), 3);
	philos = malloc(sizeof(t_philo) * info->philos_nb);
	if (!philos)
		return (free(info), free(forks), put_error("Malloc failed!"), 3);
	rvalue = init_object(&info, &philos, &forks);
	if (rvalue != 0)
		return (rvalue);
	return (monitoring(info, philos, forks));
}
