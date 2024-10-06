/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:54:44 by msloot            #+#    #+#             */
/*   Updated: 2024/10/06 19:07:55 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	create_philo(const t_arg *arg, t_manager *manager, size_t i)
{
	manager->philo_array[i].manager = manager;
	manager->philo_array[i].arg = arg;
	manager->philo_array[i].id = i + 1;
	if (pthread_create(&(manager->thread_array[i]), NULL,
			(void*)(void*)(running_philo), &(manager->philo_array[i])) != 0)
	{
		ft_puterr("an error occurred within pthread_create\n");
		return (false);
	}
	return (true);
}

bool	create_split_philo(t_manager *manager, const t_arg *arg, bool even)
{
	ssize_t	i;

	while ((size_t)i < arg->philo_amt)
	{
		if (!create_philo(arg, manager, i))
		{
			i--;
			while (i >= 0)
			{
				pthread_join(manager->thread_array[i], NULL);
				i -= (1 + even);
			}
			free(manager->thread_array);
			manager->thread_array = NULL;
			return (false);
		}
		i += 2;
	}
	return (true);
}

bool	create_thread(const t_arg *arg)
{
	t_manager	manager;

	if (!manager_init(&manager, arg))
	{
		manager_free(&manager, arg);
		return (false);
	}
	while (!manager.stop)
		usleep(420);
	write(1, "manager stopped\n", 16);
	manager_free(&manager, arg);
	return (true);
}
