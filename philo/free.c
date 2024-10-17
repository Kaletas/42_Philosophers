/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 23:53:28 by bkaleta           #+#    #+#             */
/*   Updated: 2024/10/18 00:02:45 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_all_data *all_data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < all_data->philo_number)
	{
		philo = all_data->philos + i;
		safe_mutex_handle(&philo->philo_mutex, DESTROY);
	}
	safe_mutex_handle(&all_data->write_mutex, DESTROY);
	safe_mutex_handle(&all_data->all_mutexes, DESTROY);
	free(all_data->forks);
	free(all_data->philos);
}
