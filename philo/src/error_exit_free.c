/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:14:29 by joaosilva         #+#    #+#             */
/*   Updated: 2024/07/03 00:08:43 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_callocs(t_commonstruct *table)
{
	free(table->philo);
	free(table->mutex_forks);
	free(table->taked_fork);
}

void	destroy_mutexes(t_commonstruct *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		pthread_mutex_destroy(&table->mutex_forks[i]);
		pthread_mutex_destroy(&table->philo[i].mutex_state);
	}
	pthread_mutex_destroy(&table->mutex_print);
	pthread_mutex_destroy(&table->mutex_dead);
}

// O Walter termina a função através do finish_dinner, função que é chamada
// ...que é chamada na start_dinner_monitor (monitor do Balsa).
// Esta finish_dinner basicamente é a join_threads
// ... com a junção da função destroy_mutexes e da free_callocs
int	error_exit_msg(char *msg, t_commonstruct *table, int n)
{
	if (!msg)
		return (0);
	printf("Error: %s\n", msg);
	if (n == MALLOC_ERROR)
		free_callocs(table);
	if (n == MUTEX_ERROR)
		destroy_mutexes(table);
	if (n == THREAD_ERROR)
	{
		join_threads(table);
		destroy_mutexes(table);
		free_callocs(table);
	}
	return (1);
}
