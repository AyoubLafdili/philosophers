/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:15:01 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/07 19:17:34 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <errno.h>
#include <string.h>

typedef struct s_philos_info
{
	int flag;
	int philos_nb;
	int die_time;
	int eat_time;
	int sleep_time;
	int eat_time_nb;
	time_t start;
	pthread_mutex_t _flag;
	pthread_mutex_t _start;
	pthread_mutex_t meal;
}t_pinfo;

typedef	struct s_philosopher
{
	int order;
	int meals_nb;
	pthread_t id;
	time_t	last_meal;
	t_pinfo *initial_info;
	pthread_mutex_t *p_meal;
	pthread_mutex_t *p_flag;
	pthread_mutex_t *p_start;
	pthread_mutex_t *own_fork;
	pthread_mutex_t *right_fork;
}t_philo;

void ft_sleep(t_pinfo *data, time_t amount);
time_t get_time();
int	ft_atoi(const char *str);
void *thread_func(void *param);
int pars_args(t_pinfo **init, char **args, int ac);
int forks_init(t_pinfo *info, pthread_mutex_t **to_init);
int philos_init(t_pinfo **info, t_philo **philos, pthread_mutex_t **forks);
#endif