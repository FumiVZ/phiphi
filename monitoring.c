/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 13:43:14 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/22 18:32:42 by vzuccare         ###   ########lyon.fr   */
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
		if (philo[i].nb_eat < nb_eat)
			return (false);
		i++;
	}
	return (true);
}

static int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&(philo->infos->dead_mutex));
	if (get_time() - philo->last_eat >= philo->time_to_die)
	{
		pthread_mutex_unlock(&(philo->infos->dead_mutex));
		print_message(philo, DIED);
		return (1);
	}
	pthread_mutex_unlock(&(philo->infos->dead_mutex));
	return (0);
}

void	*monitoring(void *p_info)
{
	t_info	*info;
	ssize_t	i;

	info = (t_info *)p_info;
	while (info->is_ready == false)
		ft_usleep(info->philo, 100);
	while (info->is_finished == false)
	{
		i = -1;
		while (++i < (ssize_t) info->nb_philo)
		{
			if (check_death(&info->philo[i]) == true)
			{
				info->is_finished = true;
				return (NULL);
			}
		}
		if (has_eat(info->nb_eat, info->philo) == true)
			info->is_finished = true;
		usleep(100);
	}
	return (NULL);
}
