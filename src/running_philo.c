/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:24:47 by msloot            #+#    #+#             */
/*   Updated: 2025/03/16 18:38:55 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	handle_lock(t_philo *philo, size_t first_fork, size_t second_fork)
{
	if (pthread_mutex_lock(&(philo->manager->fork_array[first_fork])) != 0)
		return (false);
	ft_putstr_fd("first fork locked\n", STDOUT_FILENO);
	if (pthread_mutex_lock(&(philo->manager->fork_array[second_fork])) != 0)
	{
		pthread_mutex_unlock(&(philo->manager->fork_array[first_fork]));
		return (false);
	}
	ft_putstr_fd("second fork locked\n", STDOUT_FILENO);
	if (!ft_print_action(philo, ACTION_FORK)
		|| !ft_print_action(philo, ACTION_FORK)
		|| !ft_print_action(philo, ACTION_EAT))
	{
		return (false);
		pthread_mutex_unlock(&(philo->manager->fork_array[second_fork]));
		ft_putstr_fd("second fork unlocked\n", STDOUT_FILENO);
		pthread_mutex_unlock(&(philo->manager->fork_array[first_fork]));
		ft_putstr_fd("first fork unlocked\n", STDOUT_FILENO);
	}
	return (true);
}

static bool	philo_eat(t_philo *philo)
{
	size_t	first_fork;
	size_t	second_fork;
	size_t	start;

	ft_putnbr_fd(philo->arg->eat_time, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	start = get_current_time();
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
	// ft_msleep(philo->arg->eat_time);
	ft_msleep(philo->arg->eat_time - (get_current_time() - start));
	pthread_mutex_unlock(&(philo->manager->fork_array[second_fork]));
	ft_print_action_raw(philo->id, "unlocked second fork");
	pthread_mutex_unlock(&(philo->manager->fork_array[first_fork]));
	ft_print_action_raw(philo->id, "unlocked first fork");
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
