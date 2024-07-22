/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:57:22 by msloot            #+#    #+#             */
/*   Updated: 2024/07/22 17:10:30 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static ssize_t	ft_putstr_fd(const char *str, int fd)
{
	return (write(fd, str, ft_strlen(str)));
}

ssize_t	ft_puterr(const char *str)
{
	ft_putstr_fd(Y_B_RED, STDERR_FILENO);
	ft_putstr_fd("Error :\t", STDERR_FILENO);
	ft_putstr_fd(Y_RESET, STDERR_FILENO);
	return (ft_putstr_fd(str, STDERR_FILENO));
}
