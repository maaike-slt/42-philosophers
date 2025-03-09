/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_action.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:01:47 by msloot            #+#    #+#             */
/*   Updated: 2025/03/09 17:19:51 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline void	ft_print_action_raw(size_t id, const char *action)
{
	printf("%zu %zu %s\n", get_current_time(), id, action);
}

void	ft_print_action(const t_philo *philo, const char *action)
{
	if (pthread_mutex_lock(&(philo->manager->print_lock)) != 0)
		return ;
	ft_print_action_raw(philo->id, action);
	pthread_mutex_unlock(&(philo->manager->print_lock));
}
