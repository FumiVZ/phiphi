/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:16:18 by vzuccare          #+#    #+#             */
/*   Updated: 2024/07/25 16:12:05 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *p_philo)
{
	t_philo	*philo;
	t_info	*info;

	philo = (t_philo *) p_philo;
	info = philo->infos;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->l_fork));
		printf("%llu %d %s\n", (get_time() - info->time), philo->id, TAKE_FORK);
		pthread_mutex_lock(&(*philo->r_fork));
		printf("%llu %d %s\n", (get_time() - info->time), philo->id, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(&(*philo->r_fork));
		printf("%llu %d %s\n", (get_time() - info->time), philo->id, TAKE_FORK);
		pthread_mutex_lock(&(philo->l_fork));
		printf("%llu %d %s\n", (get_time() - info->time), philo->id, TAKE_FORK);
	}
	printf("%llu %d %s\n", (get_time() - info->time), philo->id, EATING);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&(philo->l_fork));
	pthread_mutex_unlock(&(*philo->r_fork));
	printf("%llu %d %s\n", (get_time() - info->time), philo->id, THINKING);
	return (NULL);
}

void	init_thread(t_info *info)
{
	unsigned long long	i;

	i = 0;
	info->time = get_time();
	while (i < info->nb_philo)
	{
		if (pthread_create(&info->philo[i].thread, \
			NULL, &routine, &info->philo[i]) != 0)
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
}
