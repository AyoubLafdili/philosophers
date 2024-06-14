/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafdili <alafdili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:57:11 by alafdili          #+#    #+#             */
/*   Updated: 2024/06/14 19:17:39 by alafdili         ###   ########.fr       */
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

typedef struct s_philos_info
{
	int				philos_nb;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_time_nb;
	time_t			start;
	sem_t			*forks;
	sem_t			*s_meal;
	sem_t			*s_died;
	sem_t			*s_start;
}	t_pinfo;

typedef struct s_philosopher
{
	pid_t			pid;
	int				order;
	int				*died;
	int				meals_nb;
	t_pinfo			*shared_info;
	time_t			last_meal;
}	t_philo;

time_t	get_time(void);
int		ft_isdigit(int c);
void	put_error(char *msg);
void	ft_sleep(time_t amount);
int		ft_atoi(char *str);
int		child_func(t_philo *philo);
int		init_object(t_pinfo *info, t_philo **philo);
int		pars_args(t_pinfo *init, char **args, int ac, int *rvalue);
#endif