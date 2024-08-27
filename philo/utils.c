/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:47:29 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/27 15:11:17 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->infos->dead_mtx));
	philo->last_eat = get_time();
	pthread_mutex_unlock(&(philo->infos->dead_mtx));
	print_message(philo, EATING, philo->infos->time);
	ft_usleep(philo, philo->time_to_eat);
	pthread_mutex_lock(&(philo->r_fork->mutex));
	philo->r_fork->is_taken = -1;
	pthread_mutex_unlock(&(philo->r_fork->mutex));
	pthread_mutex_lock(&(philo->l_fork.mutex));
	philo->l_fork.is_taken = -1;
	pthread_mutex_unlock(&(philo->l_fork.mutex));
	pthread_mutex_lock(&(philo->lock));
	philo->nb_eat++;
	pthread_mutex_unlock(&(philo->lock));
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

bool	is_number(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

bool	take_fork(t_fork *fork, t_info *info, t_philo *philo)
{
	pthread_mutex_lock(&(info->dead_mtx));
	while (!info->is_finished)
	{
		pthread_mutex_unlock(&(info->dead_mtx));
		pthread_mutex_lock(&(fork->mutex));
		if (fork->is_taken == -1)
		{
			fork->is_taken = 1;
			print_message(philo, TAKE_FORK, info->time);
			pthread_mutex_unlock(&(fork->mutex));
			return (true);
		}
		pthread_mutex_unlock(&(fork->mutex));
		ft_usleep(philo, 1);
		pthread_mutex_lock(&(info->dead_mtx));
	}
	pthread_mutex_unlock(&(info->dead_mtx));
	return (false);
}

int	ft_usleep(t_philo *philo, unsigned long long time)
{
	unsigned long long	start;

	pthread_mutex_lock(&(philo->infos->dead_mtx));
	if (philo && philo->infos->is_finished)
	{
		pthread_mutex_unlock(&(philo->infos->dead_mtx));
		return (1);
	}
	pthread_mutex_unlock(&(philo->infos->dead_mtx));
	start = get_time();
	pthread_mutex_lock(&(philo->infos->dead_mtx));
	while (get_time() - start < time && !philo->infos->is_finished)
	{
		pthread_mutex_unlock(&(philo->infos->dead_mtx));
		usleep(100);
		pthread_mutex_lock(&(philo->infos->dead_mtx));
	}
	pthread_mutex_unlock(&(philo->infos->dead_mtx));
	return (0);
}
