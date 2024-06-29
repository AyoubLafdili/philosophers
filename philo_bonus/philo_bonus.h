/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:57:11 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/29 22:32:35 by alafdili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <fcntl.h>
# include <semaphore.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

# define READ "\033[1;31m"
# define END "\033[1;m"
# define YEL "\033[1;33m"
# define TOOK "has taken a fork"
# define DIED "is died"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

typedef struct s_semaphores
{
	sem_t			*s_print;
	sem_t			*s_race;
	sem_t			*forks;
	sem_t			*s_died;
	sem_t			*s_meals_nb;
} t_sem;


typedef enum e_errors_name
{
	NO_ERR,
	PARC ,
	F_MALLOC ,
	F_CREATE_TH ,
	F_INIT
} t_error;

typedef struct s_global_info
{
	int				philos_nb;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_time_nb;
	int				*flag;
	t_sem			sem;
	time_t			start;
	pthread_t		monitor_id;
}	t_pinfo;

typedef struct s_philosophers
{
	pthread_t 		id;
	pid_t			pid;
	int				order;
	int				died;
	int				meals_nb;
	time_t			last_meal;
	sem_t			*s_meal;
	t_pinfo			*shared_info;
}	t_philo;

time_t	get_time(void);
int		ft_isdigit(int c);
void	put_error(char *msg);
void	ft_sleep(time_t amount);
int		ft_atoi(char *str);
int		child_func(t_philo *philo);
int		check_flag(t_pinfo *info);
int		init_object(t_pinfo *info, t_philo **philo);
int		manda_monitor(t_pinfo *info, t_philo *philos);
int		opt_monitor(t_pinfo *info, t_philo *philos);
int		clean_up(t_philo *philo, int end);
time_t	get_timestamp(t_philo philo);
time_t get_last_meal(t_philo *philo);
int		clean_semaphores(t_pinfo *info, int order);
void	name_semaphore(char *dest, char *name, int ph_order);
int		pars_args(t_pinfo *init, char **args, int ac, int *rvalue);

#endif