/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:55:45 by vzuccare          #+#    #+#             */
/*   Updated: 2024/07/16 18:46:18 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define ERROR_ARGS \
	"./philo number_of_philosophers time_to_die time_to\
_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

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
	pthread_mutex_t		is_dead;
}						t_philo;

typedef struct s_info
{
	t_philo				*philo;
	pthread_mutex_t		*is_dead_mut;
	unsigned long long	time;
	int					nb_philo;
}						t_info;

//	===== @functions =====
// error.c
void					ft_exit_err(char *mess, int status);

// ft_atoi.c
int						ft_atoi(const char *nptr);

// ft_putstr_fd.c
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char *s, int fd);

// init.c
void					init_philo(t_info info, int ac, char **av);
void					init_info(t_info info, int ac, char **av);

#endif