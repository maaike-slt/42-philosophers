/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:24:47 by msloot            #+#    #+#             */
/*   Updated: 2024/08/21 22:32:41 by msloot           ###   ########.fr       */
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

inline bool	must_stop(t_philo *philo)
{
	if (philo->arg->max_meal && philo->meals_eaten >= philo->arg->meal_amt)
		return (true);
	if (get_current_time() - philo->last_meal > philo->arg->die_time)
	{
		philo->manager->stop = true;
		return (true);
	}
	return (false);
}

static bool	philo_eat(t_philo *philo)
{
	if (must_stop(philo))
		return (false);
	printf("eat");
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	return (true);
}

static bool	philo_sleep(t_philo *philo)
{
	if (must_stop(philo))
		return (false);
	printf("sleep");
	return (true);
}

static bool	philo_think(t_philo *philo)
{
	if (must_stop(philo))
		return (false);
	printf("think");
	return (true);
}

void	running_philo(t_philo *philo)
{
	philo->start_time = get_current_time();
	philo->last_meal = get_current_time();
	philo->meals_eaten = 0;
	while (true)
	{
		if (!philo_eat(philo))
			return ;
		if (!philo_think(philo))
			return ;
		if (!philo_sleep(philo))
			return ;
	}
}
