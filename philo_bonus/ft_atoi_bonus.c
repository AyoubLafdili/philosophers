/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:05:50 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/12 11:43:35 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(char *str)
{
	long	result;

	result = 0;
	while (*str >= 48 && *str <= 57)
	{
		result = result * 10 + *str - '0';
		if (result > 2147483647)
			return (-1);
		str++;
	}
	return (result);
}
