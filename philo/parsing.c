/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:58:52 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/01 21:51:01 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(t_ginfo *data, int *rvalue)
{
	if (data->philos_nb == -1 || !(data)->philos_nb || data->philos_nb > 200)
		return (put_error("Philo nb out of range ]0,200]!"), *rvalue = 1, 1);
	if (data->die_time == -1 || data->die_time < 60)
		return (put_error("Time to die [60,INT_MAX] Needed"), *rvalue = 1, 1);
	if (data->eat_time == -1 || data->eat_time < 60)
		return (put_error("Time to eat [60,INT_MAX] Needed"), *rvalue = 1, 1);
	if (data->sleep_time == -1 || data->sleep_time < 60)
		return (put_error("Time to sleep [60,INT_MAX] Needed"), *rvalue = 1, 1);
	if (data->eat_time_nb == -1)
		return (put_error("Eating time nb [0,INT_MAX] Needed"), *rvalue = 1, 1);
	if (data->eat_time_nb == 0)
		return (*rvalue = 0, 1);
	return (0);
}

int	init_info_struct(t_ginfo **init, char **args, int ac, int *rvalue)
{
	(*init)->philos_nb = ft_atoi(args[1]);
	(*init)->die_time = ft_atoi(args[2]);
	(*init)->eat_time = ft_atoi(args[3]);
	(*init)->sleep_time = ft_atoi(args[4]);
	(*init)->flag = 1;
	(*init)->start = 0;
	if (ac == 6)
		(*init)->eat_time_nb = ft_atoi(args[5]);
	else
		(*init)->eat_time_nb = -2;
	return (check_args(*init, rvalue));
}

int	pars_args(t_ginfo **init, char **args, int ac, int *rv)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		if (args[i][0] == '\0')
		{
			put_error("Require valid arg: Number");
			return (*rv = 1, 1);
		}
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]))
				return (put_error(""READ"Require valid arg: Number"END""),
					put_error(""YEL"NOTE: signs are execluded!"END""),
					*rv = 1, 1);
			j++;
		}
		i++;
	}
	return (init_info_struct(init, args, ac, rv));
}
