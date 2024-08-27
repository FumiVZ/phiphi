/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:35:31 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/27 15:04:12 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	ft_strtol(const char *str)
{
	int			signe;
	size_t		i;
	long int	va;

	i = 0;
	va = 0;
	signe = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			signe = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (va != ((va * 10) + str[i] - '0') / 10)
		{
			ft_putstr_fd("Error\n", 2);
		}
		va = va * 10 + str[i] - '0';
		i++;
	}
	return (va * signe);
}

static int	is_valid(char *str, long int except)
{
	long int	value;

	if (ft_strlen(str) > 11)
	{
		ft_putstr_fd("Error : value is too big\n", 2);
		return (1);
	}
	value = ft_strtol(str);
	if (value > 2147483647)
	{
		ft_putstr_fd("Error : value is too big\n", 2);
		return (1);
	}
	if (value < except)
	{
		ft_putstr_fd("Error : value must be greater than ", 2);
		ft_putnbr_fd(except, 2);
		ft_putstr_fd("\n", 2);
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

void	thread_err_exit(t_info *info, unsigned long long i)
{
	while (i--)
		pthread_detach(info->philo[i].thread);
	free_destroy(info, "Error : thread creation failed\n", 1);
}

void	ft_exit_err(char *mess, int status)
{
	if (mess)
		ft_putstr_fd(mess, 2);
	exit(status);
}
