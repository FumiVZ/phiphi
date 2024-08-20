/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:47:29 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/20 16:42:39 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_mutex(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&(philo->l_fork));
		pthread_mutex_unlock(&(*philo->r_fork));
	}
	else
	{
		pthread_mutex_unlock(&(*philo->r_fork));
		pthread_mutex_unlock(&(philo->l_fork));
	}
}

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->l_fork));
		print_message(philo, TAKE_FORK);
		pthread_mutex_lock(&(*philo->r_fork));
		print_message(philo, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(&(*philo->r_fork));
		print_message(philo, TAKE_FORK);
		pthread_mutex_lock(&(philo->l_fork));
		print_message(philo, TAKE_FORK);
	}
}

int	ft_usleep(t_philo *philo, unsigned long long time)
{
	unsigned long long	start;

	(void)philo;
	if (philo->infos->is_finished)
		return (1);
	start = get_time();
	while (get_time() - start < time)
		usleep(100);
	return (0);
}

