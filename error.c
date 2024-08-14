/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:35:31 by vzuccare          #+#    #+#             */
/*   Updated: 2024/07/30 15:30:21 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO
int	check_error(char **av)
{
	if (ft_atoi(av[1]) < 2 || ft_atoi(av[2]) < 1 || ft_atoi(av[3]) < 1 || \
		(ft_atoi(av[4]) < 1) || (av[5] && ft_atoi(av[5]) < 1))
		return (1);
	return (0);
}

void	ft_exit_err(char *mess, int status)
{
	ft_putstr_fd(mess, 2);
	exit(status);
}

void	free_exit(char *mess, int status, t_info *info)
{
	free_info(info);
	ft_exit_err(mess, status);
}
