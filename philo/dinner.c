/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 22:39:20 by bkaleta           #+#    #+#             */
/*   Updated: 2024/10/18 00:30:14 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	safe_mutex_handle(&philo->left_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mutex_handle(&philo->right_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);

	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->all_data->time_to_eat, philo->all_data);
	if (philo->all_data->meals_limit > 0
		&& philo->meals_counter == philo->all_data->meals_limit)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex_handle(&philo->left_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->right_fork->fork, UNLOCK);
}

void	thinking(t_philo *philo, bool value)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!value)
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->all_data->philo_number % 2 == 0)
		return ;
	t_eat = philo->all_data->time_to_eat;
	t_sleep = philo->all_data->time_to_sleep;
	t_think = t_eat * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->all_data);
}

void	*lone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->all_data);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increse_long(&philo->all_data->all_mutexes,
		&philo->all_data->threads_running_nbr);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!sim_finished(philo->all_data))
		usleep(200);
	return (NULL);
}

static void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->all_data);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	increse_long(&philo->all_data->all_mutexes,
		&philo->all_data->threads_running_nbr);
	de_synchro_philos(philo);
	while (!sim_finished(philo->all_data))
	{
		if (philo->full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->all_data->time_to_sleep, philo->all_data);
		thinking(philo, false);
	}
	return (NULL);
}

void	feast_begin(t_all_data *all_data)
{
	int	i;

	i = -1;
	if (0 == all_data->meals_limit)
		return ;
	else if (1 == all_data->philo_number)
		safe_thread_handle(&all_data->philos[0].thread_id,
			lone_philo, &all_data->philos[0], CREATE);
	else
	{
		while (++i < all_data->philo_number)
			safe_thread_handle(&all_data->philos[i].thread_id,
				dinner_simulation, &all_data->philos[i], CREATE);
	}
	safe_thread_handle(&all_data->monitor, monitor_dinner, all_data, CREATE);
	all_data->start = gettime(MILLISECOND);
	set_bool(&all_data->all_mutexes, &all_data->all_threads_ready, true);
	i = -1;
	while (++i < all_data->philo_number)
		safe_thread_handle(&all_data->philos[i].thread_id, NULL, NULL, JOIN);
	set_bool(&all_data->all_mutexes, &all_data->end, true);
	safe_thread_handle(&all_data->monitor, NULL, NULL, JOIN);
}
