/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:24:47 by msloot            #+#    #+#             */
/*   Updated: 2025/03/09 15:03:15 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
> • When a philosopher has finished eating, they put their forks back on the table and
> start sleeping. Once awake, they start thinking again. The simulation stops when
> a philosopher dies of starvation.

eat -> sleep -> think
 ^----------------/

odd eats
even thinks
*/

static inline bool	must_stop(t_philo *philo)
{
	if (pthread_mutex_lock(&(philo->manager->check_stop)) != 0)
		return (true);
	if (philo->manager->stop == true)
		return (pthread_mutex_unlock(&(philo->manager->check_stop)), true);
	if (philo->arg->max_meal && philo->meals_eaten >= philo->arg->meal_amt)
		return (pthread_mutex_unlock(&(philo->manager->check_stop)), true);
	if (get_current_time() - philo->last_meal > philo->arg->die_time)
	{
		philo->manager->stop = true;
		ft_print_action(philo, ACTION_DIE);
		return (pthread_mutex_unlock(&(philo->manager->check_stop)), true);
	}
	pthread_mutex_unlock(&(philo->manager->check_stop));
	return (false);
}

static bool	philo_eat(t_philo *philo)
{
	size_t	fork_index;

	if (must_stop(philo))
		return (false);
	if (pthread_mutex_lock(&(philo->manager->fork_array[philo->id - 1])) != 0)
		return (false);
	if (must_stop(philo))
	{
		pthread_mutex_unlock(&(philo->manager->fork_array[philo->id - 1]));
		return (false);
	}
	ft_print_action(philo, ACTION_FORK);
	if (philo->id == 1)
		fork_index = philo->arg->philo_amt - 1;
	else
		fork_index = philo->id - 2;
	if (pthread_mutex_lock(&(philo->manager->fork_array[fork_index])) != 0)
	{
		pthread_mutex_unlock(&(philo->manager->fork_array[philo->id - 1]));
		return (false);
	}
	if (must_stop(philo))
	{
		pthread_mutex_unlock(&(philo->manager->fork_array[philo->id - 1]));
		pthread_mutex_unlock(&(philo->manager->fork_array[fork_index]));
		return (false);
	}
	ft_print_action(philo, ACTION_FORK);
	ft_print_action(philo, ACTION_EAT);
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	ft_msleep(philo->arg->eat_time);
	pthread_mutex_unlock(&(philo->manager->fork_array[philo->id - 1]));
	pthread_mutex_unlock(&(philo->manager->fork_array[fork_index]));
	return (true);
}

static bool	philo_sleep(t_philo *philo)
{
	if (must_stop(philo))
		return (false);
	ft_print_action(philo, ACTION_SLEEP);
	ft_msleep(philo->arg->sleep_time);
	return (true);
}

static bool	philo_think(t_philo *philo)
{
	if (must_stop(philo))
		return (false);
	ft_print_action(philo, ACTION_THINK);
	return (true);
}

void	running_philo(t_philo *philo)
{
	ft_print_action(philo, "has been created");
	philo->start_time = get_current_time();
	philo->last_meal = get_current_time();
	philo->meals_eaten = 0;
	while (true)
	{
		if (!philo_eat(philo))
			break ;
		if (!philo_think(philo))
			break ;
		if (!philo_sleep(philo))
			break ;
	}
	ft_putstr_fd("outside\n", STDOUT_FILENO);
}
