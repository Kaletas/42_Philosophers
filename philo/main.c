/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 22:48:51 by bkaleta           #+#    #+#             */
/*   Updated: 2024/10/17 22:57:51 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ./philo 5 800 200 200 [5]

int	main(int ac, char **av)
{
	t_all_data	all_data;

	if (ac == 5 || ac == 6)
	{
		parse_input(&all_data, av);
		data_init(&all_data);
		feast_begin(&all_data);
		//free_all(&all_data);
	}
	else
	{
		error_exit("Correct input: ./philo 42 800 200 200 [5]'");
	}
	return (0);
}
