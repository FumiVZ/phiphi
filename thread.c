/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:16:18 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/14 18:38:00 by vzuccare         ###   ########lyon.fr   */
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

	check_death(philo);
	philo = (t_philo *)p_philo;
	info = philo->infos;
	take_fork(philo);
	eating_philo(philo);
	print_message(philo, EATING);
	ft_usleep(philo, philo->time_to_eat);
	unlock_mutex(philo);
	print_message(philo, SLEEPING);
	ft_usleep(philo, philo->time_to_sleep);
	print_message(philo, THINKING);
	check_death(philo);
	return (NULL);
}

void	init_thread(t_info *info)
{
	unsigned long long	i;

	info->time = get_time();
	while (info->nb_eat || info->nb_eat == (unsigned int) -1)
	{
		i = 0;
		while (i < info->nb_philo)
		{
			if (pthread_create(&info->philo[i].thread, NULL, &routine,
					&info->philo[i]) != 0)
				free_exit(TH_ERR, 3, info);
			if (info->philo[i].is_dead == true)
				break ;
			i++;
		}
		i = 0;
		while (i < info->nb_philo)
		{
			if (pthread_join(info->philo[i].thread, NULL) != 0)
				free_exit(TH_ERR, 3, info);
			i++;
		}
		info->nb_eat--;
	}
}
