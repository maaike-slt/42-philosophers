/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   must_stop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:23:54 by msloot            #+#    #+#             */
/*   Updated: 2025/03/09 17:39:20 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	must_stop_raw(t_philo *philo)
{
	if (philo->manager->stop == 0)
		return (true);
	if (philo->arg->max_meal && philo->meals_eaten >= philo->arg->meal_amt)
	{
		if (philo->manager->stop != 0)
			philo->manager->stop--;
		return (true);
	}
	if (get_current_time() - philo->last_meal > philo->arg->die_time)
	{
		philo->manager->stop = 0;
		ft_print_action_force(philo, ACTION_DIE);
		return (true);
	}
	return (false);
}

bool	must_stop(t_philo *philo)
{
	bool	ret;

	if (pthread_mutex_lock(&(philo->manager->check_stop)) != 0)
		return (true);
	ret = must_stop_raw(philo);
	pthread_mutex_unlock(&(philo->manager->check_stop));
	return (ret);
}
