/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:43:14 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/15 17:50:49 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	has_eat(t_info *info)
{
	size_t	i;

	i = 0;
	if (info->nb_eat == -1)
		return (false);
	while (i < info->nb_philo)
	{
		if (info->philo[i].nb_eat < info->nb_eat)
			return (false);
		i++;
	}
	return (true);
}

bool	check_ready(t_info *info)
{
	size_t	i;

	i = 0;
	while (i < info->nb_philo)
	{
		info->is_ready = true;
		i++;
	}
	return (true);
}

void	*monitoring(void *p_info)
{
	t_info	*info;
	size_t	i;

	info = (t_info *)p_info;
	if (info->is_ready == false)
		check_ready(info);
	while (info->is_dead == false && info->has_eat == false)
	{
		i = 0;
		while (++i < info->nb_philo)
		{
			pthread_mutex_lock(&info->philo[i].dead_mutex);
			if (info->philo[i].is_dead)
			{
				info->is_finished = true;
				pthread_mutex_unlock(&info->philo[i].dead_mutex);
				break ;
			}
			info->is_finished = has_eat(info);
			pthread_mutex_unlock(&info->philo[i].dead_mutex);
			i++;
		}
	}

	return (NULL);
}
