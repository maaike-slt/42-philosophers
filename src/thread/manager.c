/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 18:54:10 by msloot            #+#    #+#             */
/*   Updated: 2024/11/14 18:39:19 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	mutex_init(t_manager *manager, const t_arg *arg)
{
	ssize_t	i;

	i = 0;
	while ((size_t)i < arg->philo_amt)
	{
		if (pthread_mutex_init(&(manager->fork_array[i]), NULL) != 0)
		{
			i--;
			while (i >= 0)
			{
				pthread_mutex_destroy(&(manager->fork_array[i]));
				i--;
			}
			free(manager->fork_array);
			manager->fork_array = NULL;
			return (false);
		}
		i++;
	}
	return (true);
}

bool	manager_init(t_manager *manager, const t_arg *arg)
{
	size_t	i;

	i = 0;
	manager->stop = false;
	manager->thread_array = NULL;
	manager->fork_array = NULL;
	manager->philo_array = NULL;
	manager->philo_array = (t_philo *)malloc(sizeof(t_philo) * arg->philo_amt);
	if (!manager->philo_array)
		return (false);
	manager->fork_array = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* arg->philo_amt);
	if (!manager->fork_array)
		return (false);
	if (!mutex_init(manager, arg))
		return (false);
	manager->thread_array = (pthread_t *)malloc(sizeof(pthread_t)
			* arg->philo_amt);
	if (!manager->thread_array)
		return (false);
	while (i < arg->philo_amt)
	{
		manager->thread_array[i] = 0;
		i++;
	}
	if (!create_split_philo(manager, arg, false))
		return (false);
	if (!create_split_philo(manager, arg, true))
		return (false);
	return (true);
}

void	manager_free(t_manager *manager, const t_arg *arg)
{
	size_t	i;

	i = 0;
	while (manager->thread_array
		&& manager->thread_array[i] != 0
		&& i < arg->philo_amt)
	{
		pthread_join(manager->thread_array[i], NULL);
		i++;
	}
	free(manager->thread_array);
	manager->thread_array = NULL;
	i = 0;
	while (manager->fork_array && i < arg->philo_amt)
	{
		pthread_mutex_destroy(&(manager->fork_array[i]));
		i++;
	}
	free(manager->fork_array);
	manager->fork_array = NULL;
	free(manager->philo_array);
	manager->philo_array = NULL;
}
