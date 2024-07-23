/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:54:44 by msloot            #+#    #+#             */
/*   Updated: 2024/07/23 22:23:05 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// put in another file
void	running_philo(t_philo *philo)
{
	// init philo
	philo->start_time = 0; // set to current time with gettimeofday
	(void)philo;
	write(STDOUT_FILENO, "eat\n", 4);
	usleep(4200);
	philo->manager->stop = true;
}

bool	create_thread(const t_arg *arg)
{
	size_t		i;
	t_manager	manager;

	manager.stop = false;
	manager.thread_array = (pthread_t *)malloc(sizeof(pthread_t) * arg->philo_amt);
	if (!manager.thread_array)
		return (false);
	manager.philo_array = (t_philo *)malloc(sizeof(t_philo) * arg->philo_amt);
	if (!manager.philo_array)
		return (false);
	i = 0;
	while (i < arg->philo_amt)
	{
		manager.philo_array[i].manager = &manager;
		pthread_create(
			&(manager.thread_array[i]),
			NULL,
			(void*)(void*)(running_philo),
			&(manager.philo_array[i])
		);
		// pthread_create returns an int, probably returns some number when error
		// must catch the erro
		i++;
	}
	while (!manager.stop)
		write(STDOUT_FILENO, "the manager is sleeping\n", 24);
	return (true);
}
