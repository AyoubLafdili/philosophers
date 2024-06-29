/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:08:23 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/29 22:32:51 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int get_num_len(int nb)
{
	int i;

	i = 0;
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

void name_semaphore(char *dest, char *name, int ph_order)
{
    int i;
	int j;
	int num_len;
	char sub_name[4];

    i = 0;
    j = 0;
	num_len = get_num_len(ph_order);
	sub_name[num_len--] = '\0';
	while (ph_order != 0)
	{
		sub_name[num_len] = ph_order % 10 + '0';
		ph_order /= 10;
		num_len--;
	}
    while (name[i])
	{
        dest[i] = name[i];
		i++;
	}
	while (sub_name[j])
		dest[i++] = sub_name[j++];
    dest[i] = '\0';
}

int check_flag(t_pinfo *info)
{
	int status;

	sem_wait(info->sem.s_race);
	status = *info->flag;
	sem_post(info->sem.s_race);
	return (status);	
}

time_t get_last_meal(t_philo *philo)
{
	time_t timestamp;

	sem_wait(philo->s_meal);
	timestamp = get_time() - philo->last_meal;
	sem_post(philo->s_meal);
	return (timestamp);
}



time_t	get_timestamp(t_philo philo)
{
	return (get_time() - philo.shared_info->start);
}
void	put_error(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
		i++;
	write(2, msg, i);
	write(2, "\n", 1);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}




