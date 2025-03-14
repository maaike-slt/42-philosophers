/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:24:47 by msloot            #+#    #+#             */
/*   Updated: 2025/03/15 00:16:48 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	handle_lock(t_philo *philo, size_t first_fork, size_t second_fork)
{
	if (pthread_mutex_lock(&(philo->manager->fork_array[first_fork])) != 0)
		return (false);
	if (pthread_mutex_lock(&(philo->manager->fork_array[second_fork])) != 0)
	{
		pthread_mutex_unlock(&(philo->manager->fork_array[first_fork]));
		return (false);
	}
	if (!ft_print_action(philo, ACTION_FORK)
		|| !ft_print_action(philo, ACTION_FORK)
		|| !ft_print_action(philo, ACTION_EAT))
	{
		pthread_mutex_unlock(&(philo->manager->fork_array[second_fork]));
		pthread_mutex_unlock(&(philo->manager->fork_array[first_fork]));
		return (false);
	}
	return (true);
}

static bool	philo_eat(t_philo *philo)
{
	size_t	first_fork;
	size_t	second_fork;

	if (must_stop(philo))
		return (false);
	if (philo->id == 1)
	{
		first_fork = philo->id - 1;
		second_fork = philo->arg->philo_amt - 1;
	}
	else
	{
		first_fork = philo->id - 2;
		second_fork = philo->id - 1;
	}
	if (!handle_lock(philo, first_fork, second_fork))
		return (false);
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	ft_msleep(philo->arg->eat_time);
	pthread_mutex_unlock(&(philo->manager->fork_array[second_fork]));
	pthread_mutex_unlock(&(philo->manager->fork_array[first_fork]));
	return (true);
}

static bool	philo_sleep(t_philo *philo)
{
	if (!ft_print_action(philo, ACTION_SLEEP))
		return (false);
	ft_msleep(philo->arg->sleep_time);
	return (true);
}

static bool	philo_think(t_philo *philo)
{
	if (!ft_print_action(philo, ACTION_THINK))
		return (false);
	return (true);
}

void	running_philo(t_philo *philo)
{
	size_t	action;

	bool (*action_list[ACTION_AMOUNT])(t_philo *);
	action_list[0] = philo_eat;
	action_list[1] = philo_think;
	action_list[2] = philo_sleep;
	philo->start_time = get_current_time();
	philo->last_meal = get_current_time();
	philo->meals_eaten = 0;
	action = (philo->id % 2) * (ACTION_AMOUNT - 1);
	while (true)
	{
		if (!(action_list[action](philo)))
			break ;
		action = (action + 1) % ACTION_AMOUNT;
	}
}
