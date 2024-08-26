/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:47:29 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/26 17:41:13 by vzuccare         ###   ########lyon.fr   */
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
	int		signe;
	size_t	i;

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

bool	take_fork(pthread_mutex_t mutex, bool *var)
{
	bool	ret;

	ret = false;
	pthread_mutex_lock(&mutex);
	if (*var == false)
	{
		*var = true;
		ret = true;
	}
	pthread_mutex_unlock(&mutex);
	return (ret);
}

int	ft_usleep(t_philo *philo, unsigned long long time)
{
	unsigned long long	start;

	(void)philo;
	pthread_mutex_lock(&(philo->infos->dead_mtx));
	if (philo && philo->infos->is_finished)
	{
		pthread_mutex_unlock(&(philo->infos->dead_mtx));
		return (1);
	}
	pthread_mutex_unlock(&(philo->infos->dead_mtx));
	start = get_time();
	while (get_time() - start < time)
		usleep(100);
	return (0);
}
