/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:16:18 by vzuccare          #+#    #+#             */
/*   Updated: 2024/07/18 18:50:45 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *pointer_info)
{
	t_info	*info;

	info = (t_info *) pointer_info;
	return (NULL);
}

void	init_thread(t_info *info)
{
	unsigned long long	i;

	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_create(&info->philo[i].thread, \
			NULL, &routine, &info) != 0)
			free_exit(TH_ERR, 3, info);
		i++;
	}
}
