/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:23:53 by vzuccare          #+#    #+#             */
/*   Updated: 2024/07/18 18:45:11 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static unsigned long long	get_time(void)
{
	struct timeval		tv;
	unsigned long long	time;

	gettimeofday(&tv, NULL);
	time = (unsigned long long)(tv.tv_sec);
	time *= 1000;
	time += (unsigned long long)(tv.tv_usec);
	return (time);
}

static void	init_forks(t_philo *philo, unsigned long long nb_philo)
{
	unsigned long long	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_init(&philo[i].l_fork, NULL);
		if (i != nb_philo - 1)
			philo[i].r_fork = &philo[i + 1].l_fork;
		i++;
	}
	philo[i - 1].r_fork = &philo[0].l_fork;
}

static void	init_philo(t_info *info, int ac, char **av)
{
	unsigned long long	i;

	i = 0;
	while (i < info->nb_philo)
	{
		info->philo[i].id = i;
		info->philo[i].time_to_die = ft_atoi(av[2]);
		info->philo[i].time_to_eat = ft_atoi(av[3]);
		info->philo[i].time_to_sleep = ft_atoi(av[4]);
		if (ac != 5)
			info->philo[i].nb_eat = ft_atoi(av[6]);
		else
			info->philo[i].nb_eat = -1;
		info->philo[i].is_dead = false;
		info->philo[i].time = &info->time;
		i++;
	}
	init_forks(info->philo, info->nb_philo);
}

void	init_info(t_info *info, int ac, char **av)
{
	info->nb_philo = ft_atoi(av[1]);
	info->time = get_time();
	info->philo = malloc(sizeof(t_philo) * info->nb_philo);
	if (!info->philo)
		ft_exit_err(MALLOC_ERR, 2);
	init_philo(info, ac, av);
	init_thread(info);
}
