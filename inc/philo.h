/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:56:14 by msloot            #+#    #+#             */
/*   Updated: 2024/07/22 18:39:03 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

# include "ansi.h"

# define PHILO_MAX	200

// create t_arg struct

typedef struct s_philo
{
	pthread_t		tread;
	size_t			meals_eaten;
	size_t			last_meal;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			start_time;
	size_t			philo_amt;
	size_t			meal_amt;
	size_t			*dead;
}					t_philo;

size_t	create_thread(size_t philo_num);

ssize_t	ft_puterr(const char *str);
size_t	ft_strlen(const char *str);

#endif
