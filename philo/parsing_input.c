/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:03:53 by bkaleta           #+#    #+#             */
/*   Updated: 2024/09/23 22:32:29 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("NICE TRY! I ACCPET ONLY POSITIVE NUMBERS!\n");
	if (!is_digit(*str))
		error_exit("WRONG DIGIT \n");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("DONT BE GREEDY! INT_MAX IS THE LIMIT FOR THIS!");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	result;

	result = 0;
	str = valid_input(str);
	while (is_digit(*str))
	{
		result = (result * 10) + (*str - '0');
		str++;
	}
	if (result > INT_MAX)
		error_exit("DONT BE GREEDY! INT_MAX IS THE LIMIT FOR THIS!");
	return (result);
}

void	parse_input(t_all_data *all_data, char **av)
{
	all_data->philo_number = ft_atol(av[1]);
	all_data->time_to_die = ft_atol(av[2]) * 1000;
	all_data->time_to_eat = ft_atol(av[3]) * 1000;
	all_data->time_to_sleep = ft_atol(av[4]) * 1000;
	if (all_data->time_to_die < 60000
		|| all_data->time_to_eat < 60000
		|| all_data->time_to_sleep < 6000)
		error_exit("USE TIMESTAMPS BIGGER THEN 60ms");
	if (av[5])
		all_data->meals_limit = ft_atol(av[5]);
	else
		all_data->meals_limit = -1;
}
