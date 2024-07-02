/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:57:11 by alafdili          #+#    #+#             */
/*   Updated: 2024/07/02 18:06:10 by alafdili         ###   ########.fr       */
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
# include <sys/wait.h>

# define READ "\033[31m"
# define YEL "\033[33m"
# define END "\033[0m"

# define FORKED "has taken a fork"
# define DIED "is died"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"

enum e_exit_code
{
	SUCCES,
	FAILURE,
	PARC ,
	F_INIT ,
	F_MALLOC ,
	F_CREATE_TH
};

typedef struct s_semaphores
{
	sem_t			*s_print;
	sem_t			*s_race;
	sem_t			*forks;
	sem_t			*s_died;
	sem_t			*s_meals_nb;
}	t_sem;

typedef struct s_global_info
{
	int				ph_nb;
	int				fd;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_time_nb;
	int				*flag;
	time_t			start;
	pthread_t		monitor_id;
	t_sem			sem;
}	t_ginfo;

typedef struct s_philosophers
{
	int				order;
	int				died;
	int				meals_nb;
	pid_t			pid;
	time_t			last_meal;
	pthread_t		id;
	char			*sem_name;
	sem_t			*s_meal;
	t_ginfo			*shared_info;
}	t_philo;

time_t	get_time(void);
int		ft_isdigit(int c);
int		ft_atoi(char *str);
void	ft_sleep(time_t amount);
int		child_func(t_philo *philo);
time_t	get_timestamp(t_philo philo);
time_t	get_last_meal(t_philo *philo);
void	put_error(char *msg, char flag);
int		clean_up(t_philo *philo, int end);
void	before_exit(t_philo *philo, char *msg);
void	free_sem_names(t_philo *philo, int end);
int		clean_semaphores(t_ginfo *info, int order);
int		init_object(t_ginfo *info, t_philo **philo);
int		opt_monitor(t_ginfo *info, t_philo *philos);
int		manda_monitor(t_ginfo *info, t_philo *philos);
char	*name_semaphore(char *name, int ph_order);
int		pars_args(t_ginfo *init, char **args, int ac, int *rvalue);

#endif