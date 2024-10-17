/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:43:05 by bkaleta           #+#    #+#             */
/*   Updated: 2024/10/17 21:51:51 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_s_d(t_philo_status status, t_philo *philo, long elapsed)
//write_status_debug
{
	if (TAKE_FIRST_FORK == status && !sim_finished(philo->all_data))
		printf(W"%6ld"RST" %d has taken the 1st fork 🍽"
			"\t\t\tn"B"[🍴 %d 🍴]\n"RST, elapsed, philo->id,
			philo->left_fork->fork_id);
	else if (TAKE_SECOND_FORK == status && !sim_finished(philo->all_data))
		printf(W"%6ld"RST" %d has taken the 2nd fork 🍽"
			"\t\t\tn"B"[🍴 %d 🍴]\n"RST, elapsed, philo->id,
			philo->right_fork->fork_id);
	else if (EATING == status && !sim_finished(philo->all_data))
		printf(W"%6ld"C" %d is eating 🍲"
			"\t\t\tn"Y"[🍲 %ld 🍲]\n"RST, elapsed, philo->id,
			philo->meals_counter);
	else if (SLEEPING == status && !sim_finished(philo->all_data))
		printf(W"%6ld"RST" %d is sleeping 😴\n", elapsed, philo->id);
	else if (THINKING == status && !sim_finished(philo->all_data))
		printf(W"%6ld"RST" %d is thinking 🤔\n", elapsed, philo->id);
	else if (DIED == status)
		printf(RED"\t\t☠☠☠ %6ld %d died ☠☠☠\n"RST, elapsed, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILLISECOND) - philo->all_data->start;
	if (philo->full)
		return ;
	safe_mutex_handle(&philo->all_data->write_mutex, LOCK);
	if (debug)
		write_s_d(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !sim_finished(philo->all_data))
			printf(W"%-6ld"RST" %d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status && !sim_finished(philo->all_data))
			printf(W"%-6ld"RST" %d is eating\n"RST, elapsed, philo->id);
		else if (SLEEPING == status && !sim_finished(philo->all_data))
			printf(W"%-6ld"RST" %d is sleeping\n", elapsed, philo->id);
		else if (DIED == status)
			printf(RED"%-6ld %d died\n"RST, elapsed, philo->id);
	}
	safe_mutex_handle(&philo->all_data->write_mutex, UNLOCK);
}
