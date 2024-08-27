/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:33:47 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/27 15:00:47 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_info(t_info *info, char *mess, int status)
{
	free(info->philo);
	free(info);
	ft_exit_err(mess, status);
}

void	free_destroy(t_info *info, char *mess, int status)
{
	size_t	i;

	i = 0;
	if (!info)
		return ;
	if (info->philo)
	{
		while (i < info->nb_philo && info->philo[i].l_fork.is_taken == -1)
		{
			pthread_mutex_destroy(&(info->philo[i].l_fork.mutex));
			i++;
		}
		pthread_mutex_destroy(&(info->print_mut));
		pthread_mutex_destroy(&(info->dead_mtx));
	}
	free_info(info, mess, status);
}
