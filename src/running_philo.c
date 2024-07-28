/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 14:24:47 by msloot            #+#    #+#             */
/*   Updated: 2024/07/28 14:36:00 by msloot           ###   ########.fr       */
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
	if (philo->meals_eaten == 0)
		return (true);
	if (get_current_time() - philo->last_meal > philo->arg->die_time)
		return (philo->manager->stop = true);
	return (philo->manager->stop = false);
}

void	running_philo(t_philo *philo)
{
	// TODO: make a loop
	// in the loop, you eat, sleep, think, ... over and over again
	// before each action check if `philo->manager->stop == true`
	philo->start_time = get_current_time();
	philo->last_meal = get_current_time();
	philo->meals_eaten = 0;
	write(STDOUT_FILENO, "eat\n", 4);
	philo->last_meal = get_current_time();
	usleep(4200);
	philo->meals_eaten++;
	philo->manager->stop = true;
}
