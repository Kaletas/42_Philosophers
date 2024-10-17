/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 19:38:15 by bkaleta           #+#    #+#             */
/*   Updated: 2024/10/17 23:18:41 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_all_data *all_data)
{
	while (!get_bool(&all_data->all_mutexes, &all_data->all_threads_ready))
		;
}

long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Gettimeofday failed");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLISECOND == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSECOND == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime");
	return (42);
}

void	precise_usleep(long usec, t_all_data *all_data)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (sim_finished(all_data))
			break ;
		elapsed = gettime(MICROSECOND) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
		}
	}
}

bool	all_threads_running(t_mutex *mutex, long *threads, long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex_handle(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex_handle(mutex, UNLOCK);
	return (ret);
}

void	increse_long(t_mutex *mutex, long *value)
{
	safe_mutex_handle(mutex, LOCK);
	(*value)++;
	safe_mutex_handle(mutex, UNLOCK);
}
