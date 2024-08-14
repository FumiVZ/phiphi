/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:33:47 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/14 16:11:12 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_info(t_info *info)
{
	size_t	i;

	i = 0;
	if (!info)
		return ;
	if (info->philo)
	{
		while (i < info->nb_philo)
		{
			pthread_mutex_destroy(&(info->philo[i].l_fork));
			pthread_mutex_destroy((info->philo[i].r_fork));
			pthread_mutex_destroy(&(info->philo[i].dead_mutex));
			i++;
		}
	}
	free(info->philo);
	free(info);
}
