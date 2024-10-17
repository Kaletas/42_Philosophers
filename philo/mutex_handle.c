/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkaleta <bkaleta@student.42warsaw.pl>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:26:23 by bkaleta           #+#    #+#             */
/*   Updated: 2024/10/17 19:33:05 by bkaleta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	handle_mutex_error(int status, t_opcode opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status && (LOCK == opcode || UNLOCK == opcode))
		error_exit("The value specifed by mutex is invalid.");
	else if (EINVAL == status && INIT == opcode)
		error_exit("The value specifed by attr is invalid.");
	else if (EINVAL == status && DESTROY == opcode)
		error_exit("The mutex to be destroyed is invalid or not initialized.");
	else if (EDEADLK == status)
		error_exit("A DL would occur if the thread blocked waiting mutex.");
	else if (EPERM == status)
		error_exit("The current thread does not hold lock on mutex.");
	else if (ENOMEM == status)
		error_exit("Cannot allocate mem to create another mutex.");
	else if (EBUSY == status && (LOCK == opcode || DESTROY == opcode))
		error_exit("Mutex is locked.");
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		error_exit("Error with the malloc");
	return (ret);
}

void	safe_mutex_handle(t_mutex *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for mutex handle");
}
