/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:41:21 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/15 17:42:39 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->infos->is_dead_mut);
	if (philo->infos->is_dead == true && philo->infos->is_finished == false)
	{
		pthread_mutex_unlock(philo->infos->is_dead_mut);
		return ;
	}
	printf("%llu %d %s\n", \
		get_time() - philo->infos->time, philo->id + 1, message);
	pthread_mutex_unlock(philo->infos->is_dead_mut);
}
