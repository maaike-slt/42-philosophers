/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:52:51 by msloot            #+#    #+#             */
/*   Updated: 2024/07/23 21:47:00 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	parse(const char *s)
{
	ssize_t	n;

	n = ft_aton(s);
	// check if negative and other error
	return ((size_t)n);
}

int	main(int argc, char *argv[])
{
	t_arg	arg;

	if (argc != 5 && argc != 6)
		return (ft_puterr("wrong amount of arguments, 4 or 5 are needed\n"), 1);
	arg.philo_amt = parse(argv[1]);
	if (!arg.philo_amt)
		return (1);
	arg.die_time = ft_aton(argv[2]);
	arg.eat_time = ft_aton(argv[3]);
	arg.sleep_time = ft_aton(argv[4]);
	if (argc == 6)
	{
		arg.meal_amt = ft_aton(argv[5]);
		arg.max_meal = true;
	}
	else
		arg.max_meal = false;
	create_thread(&arg);
}
