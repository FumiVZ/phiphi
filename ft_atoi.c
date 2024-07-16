/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:11:54 by vzuccare          #+#    #+#             */
/*   Updated: 2024/07/14 16:15:39 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static long long int	ft_strtol(const char *str)
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
			exit(1);
		}
		va = va * 10 + str[i] - '0';
		i++;
	}
	return (va * signe);
}

int	ft_atoi(const char *nptr)
{
	return ((int)ft_strtol(nptr));
}