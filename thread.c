/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:16:18 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/20 16:04:16 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating_philo(t_philo *philo)
{
	philo->last_eat = get_time();
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
	while (!philo->infos->is_finished)
	{
		take_fork(philo);
		if (print_message(philo, EATING) == 1)
			return (unlock_mutex(philo), NULL);
		eating_philo(philo);
		if (ft_usleep(philo, philo->time_to_eat) == 1)
			return (unlock_mutex(philo), NULL);
		philo->nb_eat++;
		unlock_mutex(philo);
		if (print_message(philo, SLEEPING) == 1)
			return (NULL);
		if (ft_usleep(philo, philo->time_to_sleep) == 1)
			return (NULL);
		if (print_message(philo, THINKING) == 1)
			return (NULL);
		ft_usleep(philo, 10);
	}
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
			free_exit(TH_ERR, 3, info);
		i++;
	}
	if (pthread_create(&info->monitor, NULL, &monitoring, info) != 0)
		free_exit(TH_ERR, 3, info);
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
