/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:43:14 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/20 18:35:21 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	has_eat(long long nb_eat, t_philo *philo)
{
	if (nb_eat == -1)
		return (false);
	if (philo->nb_eat >= nb_eat)
		return (true);
	return (false);
}

static bool	check_ready(t_info *info)
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

static int	check_death(t_philo *philo)
{
	if (get_time() - philo->last_eat > philo->time_to_die)
	{
		pthread_mutex_lock(&(philo->dead_mutex));
		print_message(philo, DIED);
		pthread_mutex_unlock(&(philo->dead_mutex));
		return (1);
	}
	return (0);
}


void	*monitoring(void *p_info)
{
	t_info	*info;
	size_t	i;

	info = (t_info *)p_info;
	while (info->is_ready == false)
		check_ready(info);
	while (info->is_finished == false)
	{
		i = -1;
		while (++i < info->nb_philo)
		{
			if (check_death(&info->philo[i]) == true)
			{
				info->is_finished = true;
				return (NULL);
			}
			if (info->nb_eat != -1 && \
				has_eat(info->nb_eat, &info->philo[i]) == true)
			{
				info->is_finished = true;
				return (NULL);
			}
		}
	}
	return (NULL);
}
