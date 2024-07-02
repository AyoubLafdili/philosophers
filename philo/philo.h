/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:15:01 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/02 17:21:04 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define READ "\033[31m"
# define YEL "\033[33m"
# define END "\033[0m"

typedef struct s_global_info
{
	int				flag;
	int				philos_nb;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_time_nb;
	time_t			start;
	pthread_mutex_t	_flag;
	pthread_mutex_t	_start;
	pthread_mutex_t	_meal;
}	t_ginfo;

typedef struct s_philosopher
{
	int				order;
	int				meals_nb;
	pthread_t		tid;
	time_t			last_meal;
	pthread_mutex_t	*p_start;
	pthread_mutex_t	*p_meal;
	pthread_mutex_t	*p_flag;
	pthread_mutex_t	*own_fork;
	pthread_mutex_t	*right_fork;
	t_ginfo			*initial_info;
}	t_philo;

time_t	get_time(void);
int		ft_isdigit(int c);
void	put_error(char *msg);
int		ft_atoi(const char *str);
void	*thread_func(void *param);
int		check_flag(t_ginfo *info);
void	ft_sleep(t_ginfo *data, time_t amount);
void	ft_clean(t_ginfo *info, t_philo *philos);
void	ft_update_flag(t_ginfo *info, int set_val);
int		pars_args(t_ginfo **init, char **args, int ac, int *rvalue);
int		monitoring(t_ginfo *info, t_philo *philos, pthread_mutex_t *forks);
int		init_object(t_ginfo **info, t_philo **philos, pthread_mutex_t **forks);

#endif