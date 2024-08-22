/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:08:49 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/21 16:12:12 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_time(void)
{
	struct timeval		tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * (unsigned long long) 1000) + (tv.tv_usec / 1000));
}

int	main(int ac, char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if ((ac != 5 && ac != 6) || check_error(av))
		ft_exit_err(ERROR_ARGS, 1);
	info->monitor = 0;
	info->is_dead = false;
	info->has_eat = false;
	info->is_ready = false;
	info->is_finished = false;
	init_info(info, ac, av);
	init_thread(info);
	free_info(info);
	return (0);
}
