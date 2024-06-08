/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:25:31 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/08 19:15:38 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long     result;

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
