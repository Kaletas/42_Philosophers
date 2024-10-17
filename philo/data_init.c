/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:21:50 by bkaleta           #+#    #+#             */
/*   Updated: 2024/10/17 20:45:46 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_nbr;

	philo_nbr = philo->all_data->philo_number;
	philo->left_fork = &forks[(position + 1) % philo_nbr];
	philo->right_fork = &forks[position];
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &forks[position];
		philo->right_fork = &forks[(position + 1) % philo_nbr];
	}
}

static void	philo_init(t_all_data *all_data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < all_data->philo_number)
	{
		philo = all_data->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		philo->all_data = all_data;
		assign_forks(philo, all_data->forks, i);
	}
}

void	data_init(t_all_data *all_data)
{
	int	i;

	i = -1;
	all_data->end = false;
	all_data->all_threads_ready = false;
	all_data->philos = safe_malloc(sizeof(t_philo) * all_data->philo_number);
	safe_mutex_handle(&all_data->all_mutexes, INIT);
	safe_mutex_handle(&all_data->write_lock, INIT);
	all_data->forks = safe_malloc(sizeof(t_fork) * all_data->philo_number);
	while (++i < all_data->philo_number)
	{
		safe_mutex_handle(&all_data->forks[i].fork, INIT);
		all_data->forks[i].fork_id = i;
	}
	philo_init(all_data);
}
