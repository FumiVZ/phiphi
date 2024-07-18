/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:03:59 by vzuccare          #+#    #+#             */
/*   Updated: 2024/02/29 12:57:10 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tolower_str(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_tolower(int character)
{
	if (character >= 'A' && character <= 'Z')
		return (character = character + 32);
	else if (character == EOF)
		return (-1);
	else
		return (character);
}
