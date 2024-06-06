/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:58:52 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/04 18:12:52 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int init_info_struct(t_pinfo *(*init), char **args, int ac)
{
    if ((((*init))->philos_nb = ft_atoi(args[1])) == -1 || !((*init))->philos_nb
        || (*init)->philos_nb > 200)
            return (1);
    if (((*init)->die_time = ft_atoi(args[2])) == -1 || (*init)->die_time < 60)
        return (1);
    if (((*init)->eat_time  = ft_atoi(args[3])) == -1 || (*init)->eat_time < 60)
        return (1);
    if (((*init)->sleep_time = ft_atoi(args[4])) == -1 || (*init)->sleep_time < 60)
        return (1);
	if (ac == 6 && ((*init)->eat_time_nb = ft_atoi(args[5])) == -1)
			return (1);
	else
		(*init)->eat_time_nb = 0;
    (*init)->flag = 1;
    (*init)->start = 0;
    return (0);
}

int pars_args(t_pinfo **init, char **args, int ac)
{
    int i;
    int j;

    i = 1;
    while (args[i])
    {
        j = 0;
        if (args[i][0] == '\0')
            return (1);
        while (args[i][j])
        {
            if (!ft_isdigit(args[i][j]))
                return (1);
            j++;
        }
        i++;   
    }
    return (init_info_struct(init, args, ac));
}
