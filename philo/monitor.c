/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:09:19 by bkaleta           #+#    #+#             */
/*   Updated: 2024/10/17 23:41:03 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);

	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex, &philo->last_meal_time);
	t_to_die = philo->all_data->time_to_die / 1e3;

	if (elapsed > t_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	t_all_data	*all_data;
	int			i;

	all_data = (t_all_data *)data;
	while (!all_threads_running(&all_data->all_mutexes,
			&all_data->threads_running_nbr, all_data->philo_number))
		;
	while (!sim_finished(all_data))
	{
		i = 1;
		while (++i < all_data->philo_number && !sim_finished(all_data))
		{
			if (philo_died(all_data->philos + i))
			{
				set_bool(&all_data->all_mutexes, &all_data->end, true);
				write_status(DIED, all_data->philos + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}
