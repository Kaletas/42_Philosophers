/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:53:36 by bkaleta           #+#    #+#             */
/*   Updated: 2024/10/18 00:29:13 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}

void	de_synchro_philos(t_philo *philo)
{
	if (philo->all_data->philo_number % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->all_data);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}
