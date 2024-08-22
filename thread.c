/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:16:18 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/22 18:43:16 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating_philo(t_philo *philo)
{
	philo->last_eat = get_time();
}

static void	time_to_think(t_philo *philo, bool silent)
{

	philo->time_to_think = (philo->time_to_die - \
		(get_time() - philo->last_eat) - philo->time_to_eat) / 2;
	if (philo->time_to_think < 0)
		philo->time_to_think = 0;
	if (philo->time_to_think > 600)
		philo->time_to_think = 200;
	if (silent == false)
	{
		if (print_message(philo, THINKING) == 1)
			return ;
	}
	if (ft_usleep(philo, philo->time_to_think) == 1)
		return ;
}

static int	sleeping_thinking(t_philo *philo)
{
	if (print_message(philo, SLEEPING) == 1)
		return (1);
	ft_usleep(philo, philo->time_to_sleep);
	time_to_think(philo, false);
	return (0);
}

static void	*routine(void *p_philo)
{
	t_philo	*philo;

	philo = (t_philo *)p_philo;
	while (philo->infos->is_ready == false)
		usleep(100);
	philo->last_eat = get_time();
		if (philo->id % 2 != 0)
		time_to_think(philo, true);
	while (!philo->infos->is_finished)
	{
		take_fork(philo);
		if (philo->infos->nb_philo == 1)
			return (unlock_mutex(philo), NULL);
		print_message(philo, EATING);
		eating_philo(philo);
		ft_usleep(philo, philo->time_to_eat);
		philo->nb_eat++;
		unlock_mutex(philo);
		sleeping_thinking(philo);
	}
	return (NULL);
}

void	init_thread(t_info *info)
{
	unsigned long long	i;

	info->time = get_time();
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_create(&info->philo[i].thread, NULL, &routine,
				&info->philo[i]) != 0)
			free_exit(TH_ERR, 3, info);
		i++;
	}
	if (pthread_create(&info->monitor, NULL, &monitoring, info) != 0)
		free_exit(TH_ERR, 3, info);
	info->is_ready = true;
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_join(info->philo[i].thread, NULL) != 0)
			free_exit(TH_ERR, 3, info);
		i++;
	}
	if (pthread_join(info->monitor, NULL) != 0)
		free_exit(TH_ERR, 3, info);
}
