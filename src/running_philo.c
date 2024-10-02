/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:24:47 by msloot            #+#    #+#             */
/*   Updated: 2024/10/02 21:36:46 by msloot           ###   ########.fr       */
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
	if (philo->manager->stop == true)
		return (true);
	if (philo->arg->max_meal && philo->meals_eaten >= philo->arg->meal_amt)
		return (true);
	if (get_current_time() - philo->last_meal > philo->arg->die_time)
	{
		philo->manager->stop = true;
		ft_print_action(philo, ACTION_DIE);
		return (true);
	}
	return (philo->manager->stop);
}

static bool	philo_eat(t_philo *philo)
{
	if (must_stop(philo))
		return (false);
	//	lock both forks
	//	print action for each fork taken
	ft_print_action(philo, ACTION_EAT);
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	ft_msleep(philo->arg->eat_time);
	//	unlock both forks
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
	write(1, "hello\n", 6);
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
