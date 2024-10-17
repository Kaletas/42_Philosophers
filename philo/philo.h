/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:27:23 by bkaleta           #+#    #+#             */
/*   Updated: 2024/10/17 23:53:15 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define DEBUG_MODE 1
# define RST		"\033[0m"
# define RED		"\033[1;31m"
# define G			"\033[1;32m"
# define Y			"\033[1;33m"
# define B			"\033[1;34m"
# define M			"\033[1;35m"
# define C			"\033[1;36m"
# define W			"\033[1;37m"

# include <stdio.h> // printf
# include <stdlib.h> // malloc & free
# include <unistd.h> // write, usleep
# include <pthread.h> // threads, mutex
# include <stdbool.h> // bools
# include <sys/time.h> // gettimeofday
# include <limits.h> // limts such as INT_MAX & INT_MIN
# include <errno.h>

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}			t_philo_status;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time_code;

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
	t_mutex		philo_mutex;
	t_all_data	*all_data;
}	t_philo;

typedef struct s_all_data
{
	long		philo_number;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		meals_limit;
	long		start;
	long		threads_running_nbr;
	bool		end; // Philo dead or Philos full
	bool		all_threads_ready;
	t_mutex		all_mutexes;
	t_mutex		write_mutex;
	pthread_t	monitor;
	t_fork		*forks; // Array of forks
	t_philo		*philos; // Array of philos
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

// threads_handle.c
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);

// dinner.c
void	feast_begin(t_all_data *all_data);

// set_get.c
void	set_bool(t_mutex *mutex, bool *dest, bool value);
bool	get_bool(t_mutex *mutex, bool *value);
long	get_long(t_mutex *mutex, long *value);
void	set_long(t_mutex *mutex, long *dest, long value);
bool	sim_finished(t_all_data *all_data);

// utils.c
void	wait_all_threads(t_all_data *all_data);
long	gettime(t_time_code time_code);
void	precise_usleep(long usec, t_all_data *all_data);
bool	all_threads_running(t_mutex *mutex, long *threads, long philo_nbr);
void	increse_long(t_mutex *mutex, long *value);

// write.c
void	write_status(t_philo_status status, t_philo *philo, bool debug);

// monitor.c
void	*monitor_dinner(void *data);

// free.c

#endif