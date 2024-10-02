/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:54:44 by msloot            #+#    #+#             */
/*   Updated: 2024/10/02 21:30:46 by msloot           ###   ########.fr       */
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

bool	manager_init(t_manager *manager, const t_arg *arg)
{
	ssize_t	i;

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
	manager->thread_array = (pthread_t *)malloc(sizeof(pthread_t)
			* arg->philo_amt);
	if (!manager->thread_array)
		return (false);
	i = 0;
	while ((size_t)i < arg->philo_amt)
	{
		if (!create_philo(arg, manager, i))
		{
			i--;
			while (i >= 0)
			{
				pthread_join(manager->thread_array[i], NULL);
				i--;
			}
			free(manager->thread_array);
			manager->thread_array = NULL;
			return (false);
		}
		i++;
	}
	return (true);
}

void	manager_free(t_manager *manager, const t_arg *arg)
{
	size_t	i;

	i = 0;
	while (manager->thread_array && i < arg->philo_amt)
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
