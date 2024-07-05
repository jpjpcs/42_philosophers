/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers_program.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:51:09 by joaosilva         #+#    #+#             */
/*   Updated: 2024/07/03 13:23:29 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Apenas inicializamos estes 3 pq são os únicos
// que não sabemos o valor no início. E qd não 
// sabemos o valor de algo, temos de fazer malloc.
int	init_philo(t_commonstruct *table)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	while (i < table->num_philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].last_meal_time = table->start_time;
		table->philo[i].commonstruct = table;
		i++;
	}
	return (0);
}

int	init_mutexes_and_forks(t_commonstruct *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->mutex_forks[i], NULL))
			error_exit_msg("Couldn't init forks mutex", table, MUTEX_ERROR);
		if (pthread_mutex_init(&table->philo[i].mutex_state, NULL))
			error_exit_msg("Couldn't init mutex state", table, MUTEX_ERROR);
		i++;
	}
	if (pthread_mutex_init(&table->mutex_print, NULL))
		error_exit_msg("Couldn't init print mutex", table, MUTEX_ERROR);
	if (pthread_mutex_init(&table->mutex_dead, NULL))
		error_exit_msg("Couldn't init dead mutex", table, MUTEX_ERROR);
	return (0);
}

// 1ºMALLOC - // Aloca memória para os filósofos,
// que deverão ter em conta o número de filósofos. 
// Cria a estrutura de cada filósofo,
// multiplicada pelo número de filósofos.
// 2ºMALLOC - Aloca memória para os mutexes dos garfos,
// que deverão ter em conta o número de filósofos. 
// E porquê? Porque cada filósofo tem um garfo à 
// sua esquerda e outro à sua direita. Logo,
// o número de garfos é igual ao número de filósofos.
// 3ºMALLOC
// - Os garfos taken também têm de ter em conta o 
// número de filósofos. E Porquê? Porque quando um 
// filósofo pega num garfo,
// ele necessita de dois para comer. Logo,
// se 2 filósofos pegarem nos 4 garfos existentes,
// os outros dois filósofos não poderão comer.
int	init_callocs(t_commonstruct *table)
{
	table->philo = ft_calloc(table->num_philos, sizeof(t_philo));
	table->mutex_forks = ft_calloc(table->num_philos, sizeof(pthread_mutex_t));
	table->taked_fork = ft_calloc(table->num_philos, sizeof(int));
	if (!table->philo || !table->mutex_forks || !table->taked_fork)
		return (error_exit_msg("Error: Failed to allocate memory", table,
				MALLOC_ERROR));
	return (0);
}

int	init_args(t_commonstruct *table, int argc, char **argv)
{
	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->must_eat_times = ft_atoi(argv[5]);
	if (!table->num_philos || !table->time_to_die || !table->time_to_eat
		|| !table->time_to_sleep || (argc == 6 && !table->must_eat_times))
		return (error_exit_msg("Error: Invalid arguments", table,
				INVALID_ARGS));
	return (0);
}
