/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:55:45 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/22 18:25:34 by vzuccare         ###   ########lyon.fr   */
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
# define MUTEX_ERR "mutex error\n"
# define TH_ERR "thread error\n"
# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"

// Forward declaration of t_info
typedef struct s_info	t_info;

typedef struct s_fork
{
	pthread_mutex_t		mutex;
	bool				is_taken;
}						t_fork;

typedef struct s_philo
{
	int					id;
	unsigned long long	start;
	unsigned long long	last_eat;
	unsigned long long	time_to_die;
	unsigned long long	time_to_eat;
	unsigned long long	time_to_sleep;
	unsigned long long	time_to_think;
	unsigned long long	*time;
	long long			nb_eat;
	bool				is_dead;
	bool				ready;
	t_fork				l_fork;
	t_fork				*r_fork;
	pthread_t			thread;
	t_info				*infos;
}						t_philo;

typedef struct s_info
{
	t_philo				*philo;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		print_mut;
	pthread_mutex_t		eat_mut;
	unsigned long long	time;
	unsigned long long	nb_philo;
	long long			nb_eat;
	bool				is_dead;
	bool				has_eat;
	_Atomic bool		is_ready;
	bool				is_finished;
	pthread_t			monitor;
}						t_info;

//	===== @functions =====
// error.c
int						check_error(char **av);
void					ft_exit_err(char *mess, int status);
void					free_exit(char *mess, int status, t_info *info);

// free.c
void					free_info(t_info *info);

// init.c
void					init_info(t_info *info, int ac, char **av);

// main.c
unsigned long long		get_time(void);

// message.c
int						print_message(t_philo *philo, char *message);

// monitoring.c
void					*monitoring(void *p_info);

// thread.c
void					init_thread(t_info *info);

// utils.c
bool					is_number(char *str);
int						atoi_err(const char *str, long int *va);
void					unlock_mutex(t_philo *philo);
void					take_fork(t_philo *philo);
int						ft_usleep(t_philo *philo, unsigned long long time);


void					print_forks(t_philo *philo, unsigned long long nb_philo);

#endif