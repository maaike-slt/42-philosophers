/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:56:14 by msloot            #+#    #+#             */
/*   Updated: 2024/07/24 22:17:34 by msloot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>

# include "ansi.h"

# define PHILO_MAX	200

typedef struct s_arg
{
	size_t			philo_amt;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	ssize_t			meal_amt;
	bool			max_meal;
}					t_arg;

typedef struct s_manager
{
	pthread_t		*thread_array;
	struct s_philo	*philo_array;
	bool			stop;
}					t_manager;

typedef struct s_philo
{
	size_t			meals_eaten;
	size_t			last_meal;
	size_t			start_time;
	t_manager		*manager;
}					t_philo;

bool	create_thread(const t_arg *arg);
bool	parse(int argc, char *argv[]);

ssize_t	ft_putstr_fd(const char *str, int fd);
ssize_t	ft_puterr(const char *str);
size_t	ft_strlen(const char *str);
ssize_t	ft_aton(const char *nptr);
bool	ft_isdigit(char c);
bool	ft_isspace(char c);

#endif
