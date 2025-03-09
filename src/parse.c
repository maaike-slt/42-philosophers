/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 21:27:50 by msloot            #+#    #+#             */
/*   Updated: 2025/03/09 13:38:41 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_aton_check(ssize_t n)
{
	if (n <= 0)
	{
		ft_puterr(\
"one or more parameters have been assigned a number below or equal to 0, \
only positive numbers allowed\n");
		return (0);
	}
	return (n);
}

bool	parse(int argc, char *argv[], t_arg *arg)
{
	arg->philo_amt = ft_aton_check(ft_aton(argv[1]));
	if (!arg->philo_amt)
		return (false);
	arg->die_time = ft_aton_check(ft_aton(argv[2]));
	if (!arg->die_time)
		return (false);
	arg->eat_time = ft_aton_check(ft_aton(argv[3]));
	if (!arg->eat_time)
		return (false);
	arg->sleep_time = ft_aton_check(ft_aton(argv[4]));
	if (!arg->sleep_time)
		return (false);
	if (argc == 6)
	{
		arg->meal_amt = ft_aton_check(ft_aton(argv[5]));
		if (!arg->meal_amt)
			return (false);
		arg->max_meal = true;
	}
	else
		arg->max_meal = false;
	return (true);
}
