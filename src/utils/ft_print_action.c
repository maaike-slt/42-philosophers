/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:01:47 by msloot            #+#    #+#             */
/*   Updated: 2025/03/09 17:37:28 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	ft_print_action_raw(size_t id, const char *action)
{
	printf("%zu %zu %s\n", get_current_time(), id, action);
}

bool	ft_print_action_force(const t_philo *philo, const char *action)
{
	if (pthread_mutex_lock(&(philo->manager->print_lock)) != 0)
		return (false);
	ft_print_action_raw(philo->id, action);
	pthread_mutex_unlock(&(philo->manager->print_lock));
	return (true);
}

bool	ft_print_action(t_philo *philo, const char *action)
{
	bool	ret;

	if (pthread_mutex_lock(&(philo->manager->check_stop)) != 0)
		return (false);
	if (must_stop_raw(philo))
	{
		pthread_mutex_unlock(&(philo->manager->check_stop));
		return (false);
	}
	ret = ft_print_action_force(philo, action);
	pthread_mutex_unlock(&(philo->manager->check_stop));
	return (ret);
}
