/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vzuccare <vzuccare@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:08:49 by vzuccare          #+#    #+#             */
/*   Updated: 2024/07/18 18:29:06 by vzuccare         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	void_p(void);

int	main(int ac, char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if ((ac != 5 && ac != 6) || check_error(av))
		ft_exit_err(ERROR_ARGS, 1);
	init_info(info, ac, av);
	init_thread(info);
	free_info(info);
	return (0);
}
