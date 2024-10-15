/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:39:20 by bkaleta           #+#    #+#             */
/*   Updated: 2024/10/15 23:19:26 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->all_data);
	return (NULL);
}

void	feast_begin(t_all_data *all_data)
{
	int	i;

	i = -1;
	if (0 == all_data->meals_limit)
		return ;
	else if (1 == all_data->philo_number)
		;
	else
	{
		while (++i < all_data->philo_number)
			safe_thread_handle(&all_data->philos[i].thread_id,
				dinner_simulation, &all_data->philos[i], CREATE);
	}
	set_bool(&all_data->all_mutexes, &all_data->all_threads_ready, true);
}
