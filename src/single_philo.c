/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 13:27:54 by msloot            #+#    #+#             */
/*   Updated: 2025/03/09 13:44:26 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	single_philo(t_arg *arg)
{
	t_philo	p;

	p.id = 1;
	ft_msleep(arg->die_time);
	ft_print_action(&p, ACTION_DIE);
}
