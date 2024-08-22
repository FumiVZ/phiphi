/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:35:31 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/22 16:43:20 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_valid(char *str, long int except)
{
	long int	value;
	int			res;

	value = 0;
	res = atoi_err(str, &value);
	if (value < except)
	{
		ft_putstr_fd("Error : value must be greater than ", 2);
		ft_putnbr_fd(except, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (res == -1)
	{
		ft_putstr_fd("Error : value is too big\n", 2);
		return (1);
	}
	return (0);
}

int	check_error(char **av)
{
	if (is_number(av[1]) == false || is_number(av[2]) == false || \
		is_number(av[3]) == false || is_number(av[4]) == false)
		return (1);
	if (is_valid(av[1], 1) || is_valid(av[2], 1) || \
		is_valid(av[3], 1) || is_valid(av[4], 1))
		return (1);
	if (!av[5])
		return (0);
	if (is_number(av[5]) == false)
		return (1);
	if (is_valid(av[5], 1))
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
