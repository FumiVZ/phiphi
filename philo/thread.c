/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:16:18 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/27 15:15:30 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	sleeping_thinking(t_philo *philo)
{
	if (print_message(philo, SLEEPING, philo->infos->time) == 1)
		return (1);
	ft_usleep(philo, philo->time_to_sleep);
	print_message(philo, THINKING, philo->infos->time);
	return (0);
}

static void	start_routine(t_philo *philo)
{
	pthread_mutex_lock(&(philo->infos->dead_mtx));
	while (!philo->infos->is_ready)
	{
		pthread_mutex_unlock(&(philo->infos->dead_mtx));
		ft_usleep(philo, 1);
		pthread_mutex_lock(&(philo->infos->dead_mtx));
	}
	pthread_mutex_unlock(&(philo->infos->dead_mtx));
	pthread_mutex_lock(&(philo->infos->dead_mtx));
	philo->last_eat = get_time();
	pthread_mutex_unlock(&(philo->infos->dead_mtx));
	if (philo->id % 2)
		ft_usleep(philo, philo->time_to_eat);
	pthread_mutex_lock(&(philo->infos->dead_mtx));
}

static void	*routine(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *)p_philo;
	start_routine(philo);
	while (!philo->infos->is_finished)
	{
		pthread_mutex_unlock(&(philo->infos->dead_mtx));
		if (philo->infos->nb_philo != 1 && !take_fork(philo->r_fork,
				philo->infos, philo))
		{
			pthread_mutex_lock(&(philo->infos->dead_mtx));
			continue ;
		}
		if (!take_fork(&(philo->l_fork), philo->infos, philo))
		{
			pthread_mutex_lock(&(philo->infos->dead_mtx));
			continue ;
		}
		eating_philo(philo);
		sleeping_thinking(philo);
		pthread_mutex_lock(&(philo->infos->dead_mtx));
	}
	pthread_mutex_unlock(&(philo->infos->dead_mtx));
	return (NULL);
}

void	init_thread(t_info *info)
{
	unsigned long long	i;

	info->time = get_time();
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_create(&info->philo[i].thread, NULL, &routine,
				&info->philo[i]) != 0)
			thread_err_exit(info, i);
		i++;
	}
	if (pthread_create(&info->monitor, NULL, &monitoring, info) != 0)
		thread_err_exit(info, i);
	pthread_mutex_lock(&(info->dead_mtx));
	info->is_ready = true;
	pthread_mutex_unlock(&(info->dead_mtx));
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_join(info->philo[i].thread, NULL) != 0)
			free_info(info, TH_ERR, 1);
		i++;
	}
	if (pthread_join(info->monitor, NULL) != 0)
		free_info(info, TH_ERR, 1);
}
