/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:27:50 by msloot            #+#    #+#             */
/*   Updated: 2024/07/24 22:20:07 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_aton_check(ssize_t n)
{
	if (!n)
		return (0);
	if (n < 0)
	{
		ft_puterr("one or more parameters have been assigned a number below 0, \
only positive numbers allowed\n");
		return (0);
	}
	return (n);
}

bool	parse(int argc, char *argv[])
{
	t_arg	arg;

	arg.philo_amt = ft_aton_check(ft_aton(argv[1]));
	if (!arg.philo_amt || arg.philo_amt == 0)
		return (false);
	arg.die_time = ft_aton_check(ft_aton(argv[2]));
	if (!arg.die_time || arg.die_time == 0)
		return (false);
	arg.eat_time = ft_aton_check(ft_aton(argv[3]));
	if (!arg.eat_time || arg.eat_time == 0)
		return (false);
	arg.sleep_time = ft_aton_check(ft_aton(argv[4]));
	if (!arg.sleep_time || arg.sleep_time == 0)
		return (false);
	if (argc == 6)
	{
		arg.meal_amt = ft_aton_check(ft_aton(argv[5]));
		if (!arg.meal_amt || arg.meal_amt == 0)
			return (false);
		arg.max_meal = true;
	}
	else
		arg.max_meal = false;
	if (arg.sleep_time + arg.eat_time > arg.die_time)
	{
		ft_puterr("time_to_eat and time_to_sleep combined are longer \
than time_to_die, this is not possible\n");
		return (false);
	}
	return (true);
}
