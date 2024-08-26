/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:16:18 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/26 17:41:19 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *var, bool value)
{
	pthread_mutex_lock(mutex);
	*var = value;
	pthread_mutex_unlock(mutex);
}

static void	eating_philo(t_philo *philo)
{
	pthread_mutex_lock(&(philo->infos->dead_mtx));
	philo->last_eat = get_time();
	pthread_mutex_unlock(&(philo->infos->dead_mtx));
	print_message(philo, EATING, philo->infos->time);
	ft_usleep(philo, philo->time_to_eat);
	pthread_mutex_lock(&(philo->l_fork.mutex));
	pthread_mutex_lock(&(philo->r_fork->mutex));
	philo->l_fork.is_taken = false;
	philo->r_fork->is_taken = false;
	pthread_mutex_unlock(&(philo->l_fork.mutex));
	pthread_mutex_unlock(&(philo->r_fork->mutex));
	pthread_mutex_lock(&(philo->lock));
	philo->nb_eat++;
	pthread_mutex_unlock(&(philo->lock));
}

static int	eat_sleeping_thinking(t_philo *philo)
{
	eating_philo(philo);
	if (print_message(philo, SLEEPING, philo->infos->time) == 1)
		return (1);
	ft_usleep(philo, philo->time_to_sleep);
	print_message(philo, THINKING, philo->infos->time);
	usleep(1);
	return (0);
}

static void	start_routine(t_philo *philo)
{
	while (!get_bool(&(philo->infos->dead_mtx), &(philo->infos->is_ready)))
		usleep(100);
	pthread_mutex_lock(&(philo->infos->dead_mtx));
	philo->last_eat = get_time();
	pthread_mutex_unlock(&(philo->infos->dead_mtx));
	if (philo->id % 2 != 0)
		ft_usleep(philo, philo->time_to_eat / 10);
}

static void	*routine(void *p_philo)
{
	t_philo	*philo;
	bool	left;
	bool	right;

	left = false;
	right = false;
	philo = (t_philo *)p_philo;
	start_routine(philo);
	while (get_bool(&(philo->infos->dead_mtx),
			&(philo->infos->is_finished)) == false)
	{
		if (!left)
			left = take_fork(philo->l_fork.mutex, &philo->l_fork.is_taken);
		if (!right)
			right = take_fork(philo->r_fork->mutex, &philo->r_fork->is_taken);
		if (right && left)
			eat_sleeping_thinking(philo);
		right = false;
		left = false;
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
	set_bool(&info->dead_mtx, &info->is_ready, true);
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
