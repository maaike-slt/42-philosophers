/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:52:51 by msloot            #+#    #+#             */
/*   Updated: 2024/07/22 18:19:19 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_philo	philo;

	if (argc != 5 && argc != 6)
		return (ft_puterr("wrong amount of arguments, 4 or 5 are needed\n"), 1);
	philo.philo_amt = argv[1];
	philo.die_time = argv[2];
	philo.eat_time = argv[3];
	philo.sleep_time = argv[4];
	if (argc == 6)
		philo.meal_amt = argv[5];
		// if argc != 6 the meal_amt will not be initialize, you must initialize it
}
