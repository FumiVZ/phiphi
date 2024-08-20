/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:41:21 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/20 18:30:26 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->infos->print_mut);
	if (philo->infos->is_finished == true)
	{
		pthread_mutex_unlock(&philo->infos->print_mut);
		return (1);
	}
	printf("%llu %d %s\n", get_time() - philo->infos->time, philo->id + 1,
		message);
	pthread_mutex_unlock(&philo->infos->print_mut);
	return (0);
}
