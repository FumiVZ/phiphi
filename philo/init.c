/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:23:53 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/27 15:02:20 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_forks(t_philo *philo, unsigned long long nb_philo)
{
	unsigned long long	i;

	i = 0;
	while (i < nb_philo)
	{
		printf("philo[%llu].l_fork = %p\n", i, &philo[i].l_fork);
		printf("philo[%llu].r_fork = %p\n", i, philo[i].r_fork);
		i++;
	}
}

static void	init_forks(t_philo *philo, unsigned long long nb_philo)
{
	long long	i;

	i = -1;
	while (++i < (long long) nb_philo)
		philo[i].l_fork.is_taken = -2;
	if (nb_philo == 1)
	{
		if (pthread_mutex_init(&philo[0].l_fork.mutex, NULL))
			ft_exit_err(MUTEX_ERR, 2);
		philo[0].l_fork.is_taken = 0;
		return ;
	}
	i = 0;
	while (i < (long long) nb_philo)
	{
		if (pthread_mutex_init(&philo[i].l_fork.mutex, NULL))
			free_destroy(philo->infos, MUTEX_ERR, 1);
		philo[i].l_fork.is_taken = -1;
		if (i == 0)
			philo[i].r_fork = &philo[nb_philo - 1].l_fork;
		else
			philo[i].r_fork = &philo[i - 1].l_fork;
		i++;
	}
}

static void	init_basic(t_info *info, int ac, char **av, unsigned long long i)
{
	info->philo[i].id = i;
	info->philo[i].time_to_die = ft_atoi(av[2]);
	info->philo[i].time_to_eat = ft_atoi(av[3]);
	info->philo[i].time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		info->nb_eat = ft_atoi(av[5]);
	else
		info->nb_eat = -1;
	info->philo[i].nb_eat = 0;
	info->philo[i].is_dead = false;
	info->philo[i].infos = info;
	info->philo[i].last_eat = get_time();
	info->philo[i].ready = false;
}

static void	init_philo(t_info *info, int ac, char **av)
{
	unsigned long long	i;

	i = 0;
	while (i < info->nb_philo)
	{
		init_basic(info, ac, av, i);
		if (pthread_mutex_init(&info->philo[i].lock, NULL))
			free_info(info, MUTEX_ERR, 1);
		i++;
	}
	if (pthread_mutex_init(&info->print_mut, NULL))
	{
		while (i--)
			pthread_mutex_destroy(&info->philo[i].lock);
		free_info(info, MUTEX_ERR, 1);
	}
	if (pthread_mutex_init(&info->dead_mtx, NULL))
	{
		while (i--)
			pthread_mutex_destroy(&info->philo[i].lock);
		pthread_mutex_destroy(&info->print_mut);
		free_info(info, MUTEX_ERR, 1);
	}
	init_forks(info->philo, info->nb_philo);
}

void	init_info(t_info *info, int ac, char **av)
{
	info->nb_philo = ft_atoi(av[1]);
	info->philo = malloc(sizeof(t_philo) * info->nb_philo);
	info->philo->time_to_think = 0;
	if (!info->philo)
		ft_exit_err(MALLOC_ERR, 2);
	if (!info->philo)
		ft_exit_err(MALLOC_ERR, 2);
	init_philo(info, ac, av);
	init_thread(info);
}
