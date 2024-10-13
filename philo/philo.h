/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:27:23 by bkaleta           #+#    #+#             */
/*   Updated: 2024/10/13 22:55:06 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // printf
# include <stdlib.h> // malloc & free
# include <unistd.h> // write, usleep
# include <pthread.h> // threads, mutex
# include <stdbool.h> // bools
# include <sys/time.h> // gettimeofday
# include <limits.h> // limts such as INT_MAX & INT_MIN
# include <errno.h>

typedef enum e_opcode
{
	LOCK = 0,
	UNLOCK = 1,
	INIT = 2,
	DESTROY = 3,
	CREATE = 4,
	JOIN = 5,
	DETACH = 6,
}			t_opcode;

typedef pthread_mutex_t		t_mutex;

typedef struct s_all_data	t_all_data;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int			id; // amount of philosophers
	long		meals_counter; // amount of meals eaten by certain philo
	bool		full; // flag to check if philo ate all that he/she could
	long		last_meal_time; // time passed form last meal
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_all_data	*all_data;
}	t_philo;

typedef struct s_all_data
{
	long	philo_number;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	meals_limit;
	long	start;
	bool	end; // Philo dead or Philos full
	t_fork	*forks; // Array of forks
	t_fork	*philos; // Array of philos
}	t_all_data;

// error_handlig.c
void	error_exit(const char *error);

// parsing_input.c
void	parse_input(t_all_data *all_data, char **av);

// data_init.c
void	data_init(t_all_data *all_data);

// mutex_handle.c
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mutex *mutex, t_opcode opcode);

#endif