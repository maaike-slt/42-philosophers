/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:52:51 by msloot            #+#    #+#             */
/*   Updated: 2025/03/09 13:47:53 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_arg	arg;

	if (argc != 5 && argc != 6)
		return (ft_puterr("wrong amount of arguments, 4 or 5 are needed\n"), 1);
	if (!parse(argc, argv, &arg))
		return (1);
	if (argv[1][0] == '1' && argv[1][1] == '\0')
		return (single_philo(&arg), 0);
	if (!create_thread(&arg))
		return (1);
	return (0);
}
