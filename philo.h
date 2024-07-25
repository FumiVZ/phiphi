/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:55:45 by vzuccare          #+#    #+#             */
/*   Updated: 2024/07/25 16:04:12 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/ft_printf.h"
# include "libft/libft.h"
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERROR_ARGS \
	"./philo number_of_philosophers time_to_die time_to\
_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"
# define MALLOC_ERR "malloc failed\n"
# define TH_ERR "thread error\n"
# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

// Forward declaration of t_info
typedef struct s_info	t_info;

typedef struct s_philo
{
	int					id;
	unsigned long long	start;
	unsigned int		nb_eat;
	unsigned long long	last_eat;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	*time;
	bool				is_dead;
	pthread_mutex_t		l_fork;
	pthread_mutex_t		*r_fork;
	pthread_t			thread;
	pthread_mutex_t		dead_mutex;
	t_info				*infos;
}						t_philo;

typedef struct s_info
{
	t_philo				*philo;
	pthread_mutex_t		*is_dead_mut;
	unsigned long long	time;
	unsigned long long	nb_philo;
}						t_info;

//	===== @functions =====
// free.c
void					free_info(t_info *info);

// init.c
void					init_info(t_info *info, int ac, char **av);

// error.c
int						check_error(char **av);
void					ft_exit_err(char *mess, int status);
void					free_exit(char *mess, int status, t_info *info);

// thread.c
void					init_thread(t_info *info);

// main.c
unsigned long long		get_time(void);

#endif