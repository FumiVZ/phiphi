/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:15:35 by vzuccare          #+#    #+#             */
/*   Updated: 2024/08/26 13:15:26 by vzuccare         ###   ########lyon.fr   */
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
			ft_putstr_fd("Error\n", 1);
			exit(0);
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

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n = n * -1;
		write(fd, "-", 1);
	}
	if (n > 9)
		ft_putnbr_fd((n / 10), fd);
	ft_putchar_fd(((n % 10) + '0'), fd);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
