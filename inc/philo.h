/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msloot <msloot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:56:14 by msloot            #+#    #+#             */
/*   Updated: 2025/03/16 17:52:26 by msloot           ###   ########.fr       */
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
// # define MICRO_TIME (1000 - 100)

# define ACTION_AMOUNT	3
# define ACTION_FORK	"has taken a fork"
# define ACTION_EAT		"is eating"
# define ACTION_SLEEP	"is sleeping"
# define ACTION_THINK	"is thinking"
# define ACTION_DIE		"died"

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
	pthread_mutex_t	*fork_array;
	struct s_philo	*philo_array;
	pthread_mutex_t	check_stop;
	size_t			stop;
	pthread_mutex_t	print_lock;
}					t_manager;

typedef struct s_philo
{
	size_t			id;
	size_t			meals_eaten;
	size_t			last_meal;
	size_t			start_time;
	const t_arg		*arg;
	t_manager		*manager;
}					t_philo;

bool	parse(int argc, char *argv[], t_arg *arg);
bool	create_thread(const t_arg *arg);
bool	create_split_philo(t_manager *manager, const t_arg *arg, bool even);
void	running_philo(t_philo *philo);
void	single_philo(t_arg *arg);

bool	must_stop(t_philo *philo);
bool	must_stop_raw(t_philo *philo);

void	manager_free(t_manager *manager, const t_arg *arg);
bool	manager_init(t_manager *manager, const t_arg *arg);

ssize_t	ft_putstr_fd(const char *str, int fd);
void	ft_putnbr_fd(size_t n, int fd);
ssize_t	ft_puterr(const char *str);
size_t	ft_strlen(const char *str);
ssize_t	ft_aton(const char *nptr);
bool	ft_isdigit(char c);
bool	ft_isspace(char c);
size_t	get_current_time(void);
void	ft_msleep(size_t ms);
bool	ft_print_action(t_philo *philo, const char *action);
bool	ft_print_action_force(const t_philo *philo, const char *action);
void	ft_print_action_raw(size_t id, const char *action);
void	ft_free_2d(void ***arr, size_t size);

#endif
