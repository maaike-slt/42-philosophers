/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:54:44 by msloot            #+#    #+#             */
/*   Updated: 2024/07/17 16:39:13 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	create_thread(size_t t_philo philo)
{
	pthread_t	ober;
	size_t		i;

	i = 0;
	pthread_create(ober, NULL, X, X);
	while (i < philo->philo_amt)
	{
		pthread_create(philo[i].thread, NULL, X, philo[i]);
		i++;
	}
}
