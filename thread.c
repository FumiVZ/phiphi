/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:16:18 by vzuccare          #+#    #+#             */
/*   Updated: 2024/07/24 19:05:57 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *) p_philo;
	pthread_mutex_lock(&(philo->l_fork));
	printf("%llu %d %s\n", (get_time() - *philo->time), philo->id, TAKE_FORK);
	pthread_mutex_lock(&(*philo->r_fork));
	printf("%llu %d %s\n", (get_time() - *philo->time), philo->id, TAKE_FORK);
	pthread_mutex_unlock(&(philo->l_fork));
	pthread_mutex_unlock(&(*philo->r_fork));
	return (NULL);
}

void	init_thread(t_info *info)
{
	unsigned long long	i;

	i = 0;
	printf("TIME: %llu\n", (get_time() - *info->philo[0].time));
	while (i < info->nb_philo)
	{
		info->philo[i].time = &info->time;
		if (pthread_create(&info->philo[i].thread, \
			NULL, &routine, &info->philo[i]) != 0)
			free_exit(TH_ERR, 3, info);
		if (info->philo[i].is_dead == true)
			break ;
		if (pthread_join(info->philo[i].thread, NULL) != 0)
			free_exit(TH_ERR, 3, info);
		i++;
	}
}
