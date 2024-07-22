/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:54:44 by msloot            #+#    #+#             */
/*   Updated: 2024/07/22 22:23:32 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	create_thread(t_arg *arg)
{
	size_t	i;
	t_philo	philo;
	t_philo	**philo_array; //malloc that

	i = 0;
	philo_array = (t_philo **)malloc(sizeof(t_philo *) * arg->philo_amt);
	while (i < arg->philo_amt)
	{
		philo_array[i] = (t_philo *)malloc(sizeof(t_philo) * 5);
		// init philo struct
		pthread_create(philo[i].thread, NULL, running_philo, philo);
		i++;
	}

	// once once philo is dead, stop everything
}

void	running_philo(t_philo *philo)
{
	ft_putstr("eat\n");
}
