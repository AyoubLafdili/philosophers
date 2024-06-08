/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:15:01 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/08 22:24:57 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include "track_leaks.h"

typedef struct s_philos_info
{
	int flag;
	int philos_nb;
	int die_time;
	int eat_time;
	int sleep_time;
	int eat_time_nb;
	time_t start_sim;
	pthread_mutex_t _flag;
	pthread_mutex_t _start;
	pthread_mutex_t meal;
}t_pinfo;

typedef	struct s_philosopher
{
	int				order;
	int				meals_nb;
	time_t			last_meal;
	t_pinfo			*initial_info;
	pthread_t		id;
	pthread_mutex_t	*p_meal;
	pthread_mutex_t	*p_flag;
	pthread_mutex_t	*p_start;
	pthread_mutex_t	*own_fork;
	pthread_mutex_t	*right_fork;
}t_philo;

time_t	get_time();
int		ft_isdigit(int c);
void	put_error(char *msg);
int		ft_atoi(const char *str);
void	*thread_func(void *param);
void	ft_sleep(t_pinfo *data, time_t amount);
int		pars_args(t_pinfo **init, char **args, int ac, int *rvalue);
int		init_object(t_pinfo **info, t_philo **philos, pthread_mutex_t **forks);
void	ft_clean(t_pinfo *info, t_philo *philos);
#endif