/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:47:29 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/22 18:21:37 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_number(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	atoi_err(const char *str, long int *va)
{
	int			signe;
	size_t		i;

	i = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			signe = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (*va != ((*va * 10) + str[i] - '0') / 10)
			return (-1);
		*va = *va * 10 + str[i] - '0';
		i++;
	}
	*va *= signe;
	return (1);
}

void	unlock_mutex(t_philo *philo)
{
	if (philo->infos->nb_philo == 1)
	{
		philo->l_fork.is_taken = false;
		pthread_mutex_unlock(&(philo->l_fork.mutex));
	}
	else if (philo->id % 2 == 0)
	{
		philo->l_fork.is_taken = false;
		philo->r_fork->is_taken = false;
		pthread_mutex_unlock(&(philo->l_fork.mutex));
		pthread_mutex_unlock(&(philo->r_fork->mutex));
	}
	else
	{
		philo->l_fork.is_taken = false;
		philo->r_fork->is_taken = false;
		pthread_mutex_unlock(&(philo->r_fork->mutex));
		pthread_mutex_unlock(&(philo->l_fork.mutex));
	}
}

void	take_fork(t_philo *philo)
{
	if (philo->infos->nb_philo == 1)
	{
		pthread_mutex_lock(&(philo->l_fork.mutex));
		print_message(philo, TAKE_FORK);
		philo->l_fork.is_taken = true;
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->l_fork.mutex));
		philo->l_fork.is_taken = true;
		print_message(philo, TAKE_FORK);
		pthread_mutex_lock(&(philo->r_fork->mutex));
		philo->r_fork->is_taken = true;
		print_message(philo, TAKE_FORK);
	}
	else
	{
		pthread_mutex_lock(&(philo->l_fork.mutex));
		philo->l_fork.is_taken = true;
		print_message(philo, TAKE_FORK);
		pthread_mutex_lock(&(philo->r_fork->mutex));
		philo->r_fork->is_taken = true;
		print_message(philo, TAKE_FORK);
	}
}

int	ft_usleep(t_philo *philo, unsigned long long time)
{
	unsigned long long	start;

	(void)philo;
	if (philo && philo->infos->is_finished)
		return (1);
	start = get_time();
	while (get_time() - start < time)
		usleep(100);
	return (0);
}
