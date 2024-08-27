/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:43:14 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/27 11:09:23 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	has_eat(long long nb_eat, t_philo *philo)
{
	size_t	i;

	i = 0;
	if (nb_eat == -1)
		return (false);
	while (i < philo->infos->nb_philo)
	{
		pthread_mutex_lock(&(philo[i].lock));
		if (philo[i].nb_eat < nb_eat)
		{
			pthread_mutex_unlock(&(philo[i].lock));
			return (false);
		}
		pthread_mutex_unlock(&(philo[i].lock));
		i++;
	}
	return (true);
}

static int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&(philo->infos->dead_mtx));
	if (get_time() - philo->last_eat > philo->time_to_die)
	{
		pthread_mutex_unlock(&(philo->infos->dead_mtx));
		print_message(philo, DIED, philo->infos->time - 5);
		return (1);
	}
	pthread_mutex_unlock(&(philo->infos->dead_mtx));
	return (0);
}

static int	check_death_eat(t_info *info)
{
	ssize_t	i;

	pthread_mutex_unlock(&(info->dead_mtx));
	i = -1;
	while (++i < (ssize_t)info->nb_philo)
	{
		if (check_death(&info->philo[i]) == true)
		{
			pthread_mutex_lock(&(info->dead_mtx));
			info->is_finished = true;
			pthread_mutex_unlock(&(info->dead_mtx));
			return (1);
		}
	}
	if (has_eat(info->nb_eat, info->philo) == true)
	{
		pthread_mutex_lock(&(info->dead_mtx));
		info->is_finished = true;
		pthread_mutex_unlock(&(info->dead_mtx));
	}
	pthread_mutex_lock(&(info->dead_mtx));
	return (0);
}

void	*monitoring(void *p_info)
{
	t_info	*info;

	info = (t_info *)p_info;
	pthread_mutex_lock(&(info->dead_mtx));
	while (info->is_ready == false)
	{
		pthread_mutex_unlock(&(info->dead_mtx));
		ft_usleep(info->philo, 100);
		pthread_mutex_lock(&(info->dead_mtx));
	}
	pthread_mutex_unlock(&(info->dead_mtx));
	pthread_mutex_lock(&(info->dead_mtx));
	while (info->is_finished == false)
	{
		if (check_death_eat(info) == 1)
			return (NULL);
	}
	pthread_mutex_unlock(&(info->dead_mtx));
	return (NULL);
}
