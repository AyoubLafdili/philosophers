/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:01:37 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/28 22:13:54 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_args(t_pinfo *data)
{
	if (data->philos_nb == -1 || !(data)->philos_nb || data->philos_nb > 200)
		return (put_error("Philo nb out of range ]0,200]!"), 1);
	if (data->die_time == -1 || data->die_time < 60)
		return (put_error("Time to die [60,INT_MAX] Needed"), 1);
	if (data->eat_time == -1 || data->eat_time < 60)
		return (put_error("Time to eat [60,INT_MAX] Needed"), 1);
	if (data->sleep_time == -1 || data->sleep_time < 60)
		return (put_error("Time to sleep [60,INT_MAX] Needed"), 1);
	if (data->eat_time_nb == -1)
		return (put_error("Eating time nb [0,INT_MAX] Needed"), 1);
	if (data->eat_time_nb == 0)
		return (2);
	return (NO_ERR);
}

int	init_info_struct(t_pinfo *init, char **args, int ac, int *rvalue)
{
	init->philos_nb = ft_atoi(args[1]);
	init->die_time = ft_atoi(args[2]);
	init->eat_time = ft_atoi(args[3]);
	init->sleep_time = ft_atoi(args[4]);
	if (ac == 6)
		init->eat_time_nb = ft_atoi(args[5]);
	else
		init->eat_time_nb = -2;
	init->flag = malloc(sizeof(int));
	if (!init->flag)
		return (put_error("Malloc failed!"), F_MALLOC);
	*init->flag = 0;
	*rvalue = check_args(init);
	if (*rvalue != 0)
	{
		if (*rvalue == 2)
			*rvalue = 0;
		return (free(init->flag), 1);
	}
	return (NO_ERR);	
}
int pars_args(t_pinfo *init, char **args, int ac, int *rv)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][0] == '\0')
			return (put_error("Require valid arg: Number"), *rv = PARC, PARC);
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]))
				return (put_error(""READ"Require valid arg: Number"END""),
					put_error(""YEL"NOTE: signs are execluded!"END""),
					*rv = PARC, PARC);
			j++;
		}
		i++;
	}
	return (init_info_struct(init, args, ac, rv));
}
