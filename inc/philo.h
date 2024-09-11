/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:56:14 by msloot            #+#    #+#             */
/*   Updated: 2024/09/11 21:52:29 by msloot           ###   ########.fr       */
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
# include <sys/time.h>

# include "ansi.h"

# define PHILO_MAX	200

typedef struct s_arg
{
	size_t			philo_amt;
	size_t			die_time;
	size_t			eat_time;
	size_t			sleep_time;
	size_t			meal_amt;
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
	size_t			index;
	size_t			meals_eaten;
	size_t			last_meal;
	size_t			start_time;
	const t_arg		*arg;
	t_manager		*manager;
}					t_philo;

bool	parse(int argc, char *argv[], t_arg *arg);
bool	create_thread(const t_arg *arg);
void	running_philo(t_philo *philo);

ssize_t	ft_putstr_fd(const char *str, int fd);
void	ft_putnbr_fd(size_t n, int fd);
ssize_t	ft_puterr(const char *str);
size_t	ft_strlen(const char *str);
ssize_t	ft_aton(const char *nptr);
bool	ft_isdigit(char c);
bool	ft_isspace(char c);
size_t	get_current_time(void);
void	ft_msleep(size_t ms);

#endif
