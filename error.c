/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:35:31 by vzuccare          #+#    #+#             */
/*   Updated: 2024/07/18 18:48:15 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO
int	check_error(char **av)
{
	(void)av;
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
