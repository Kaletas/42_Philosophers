/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:27:23 by bkaleta           #+#    #+#             */
/*   Updated: 2024/09/22 21:44:56 by bkaleta          ###   ########.fr       */
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

typedef pthread_mutex_t	t_mutex;

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
}	t_philo;

#endif