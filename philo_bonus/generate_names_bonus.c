/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_names_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 18:29:53 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/30 21:58:49 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_num_len(int nb)
{
	int	i;

	i = 0;
	while (nb != 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

void	ft_strcatcpy(char *dest, char *name_src, char *num_src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (name_src[i])
	{
		dest[i] = name_src[i];
		i++;
	}
	while (num_src[j])
		dest[i++] = num_src[j++];
	dest[i] = '\0';
}

char	*name_semaphore(char *name, int ph_order)
{
	int		num_len;
	char	*dest;
	char	sub_name[4];

	num_len = get_num_len(ph_order);
	dest = malloc((num_len + 6) * sizeof(char));
	if (!dest)
		return (NULL);
	sub_name[num_len--] = '\0';
	while (ph_order != 0)
	{
		sub_name[num_len] = ph_order % 10 + '0';
		ph_order /= 10;
		num_len--;
	}
	ft_strcatcpy(dest, name, sub_name);
	return (dest);
}
