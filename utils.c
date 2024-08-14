/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:47:29 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/14 18:38:15 by vzuccare         ###   ########lyon.fr   */
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

void	check_death(t_philo *philo)
{
	if (get_time() - philo->last_eat > philo->time_to_die)
	{
		pthread_mutex_lock(&(philo->dead_mutex));
		print_message(philo, DIED);
		philo->is_dead = true;
		pthread_mutex_unlock(&(philo->dead_mutex));
	}
}

void	ft_usleep(t_philo *philo, unsigned long long time)
{
	unsigned long long	start;

	start = get_time();
	while (get_time() - start < time && !philo->is_dead)
	{
		usleep(100);
		check_death(philo);
	}
}
