/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:16:18 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/15 17:56:52 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->dead_mutex));
	philo->last_eat = get_time();
	pthread_mutex_unlock(&(philo->dead_mutex));
}

static void	*routine(void *p_philo)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *)p_philo;
	info = philo->infos;
	philo->ready = true;
	while (info->is_ready == false)
		usleep(10);
	while (!philo->infos->is_finished && philo->nb_eat < philo->infos->nb_eat)
	{
		take_fork(philo);
		eating_philo(philo);
		print_message(philo, EATING);
		if (ft_usleep(philo, philo->time_to_eat))
		{
			unlock_mutex(philo);
			break ;
		}
		philo->nb_eat++;
		unlock_mutex(philo);
		print_message(philo, SLEEPING);
		if (ft_usleep(philo, philo->time_to_sleep))
			break ;
		print_message(philo, THINKING);
	}
	return (NULL);
}

void	init_thread(t_info *info)
{
	unsigned long long	i;

	info->time = get_time();
	while (!info->is_finished)
	{
		i = 0;
		while (i < info->nb_philo)
		{
			if (pthread_create(&info->philo[i].thread, NULL, &routine,
					&info->philo[i]) != 0)
				free_exit(TH_ERR, 3, info);
			i++;
		}
		if (pthread_create(&info->monitor, NULL, &monitoring, info) != 0)
			free_exit(TH_ERR, 3, info);
	}
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_join(info->philo[i].thread, NULL) != 0)
			free_exit(TH_ERR, 3, info);
		i++;
	}
	if (pthread_join(info->monitor, NULL) != 0)
		free_exit(TH_ERR, 3, info);
}
