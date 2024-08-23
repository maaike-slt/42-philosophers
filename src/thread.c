/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:54:44 by msloot            #+#    #+#             */
/*   Updated: 2024/08/23 19:31:28 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	create_philo(const t_arg *arg, t_manager *manager, size_t i)
{
	manager->philo_array[i].manager = manager;
	manager->philo_array[i].arg = arg;
	manager->philo_array[i].index = i;
	if (pthread_create(&(manager->thread_array[i]), NULL,
			(void*)(void*)(running_philo), &(manager->philo_array[i])) != 0)
	{
		ft_puterr("an error occurred within pthread_create\n");
		return (false);
	}
	return (true);
}

bool	create_thread(const t_arg *arg)
{
	size_t		i;
	t_manager	manager;

	manager.stop = false;
	manager.thread_array = (pthread_t *)malloc(sizeof(pthread_t)
			* arg->philo_amt);
	if (!manager.thread_array)
		return (false);
	manager.philo_array = (t_philo *)malloc(sizeof(t_philo) * arg->philo_amt);
	if (!manager.philo_array)
		return (false);
	i = 0;
	while (i < arg->philo_amt)
	{
		if (!create_philo(arg, &manager, i))
			return (false);
		i++;
	}
	while (!manager.stop)
		usleep(420);
	write(1, "manager stopped\n", 16);
	return (true);
}
