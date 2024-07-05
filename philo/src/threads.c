/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 12:47:10 by joaosilva         #+#    #+#             */
/*   Updated: 2024/07/03 00:13:08 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->commonstruct->mutex_print);
	printf("%llu %d%s", get_time() - philo->commonstruct->start_time, philo->id,
		DIED);
	pthread_mutex_unlock(&philo->commonstruct->mutex_print);
}

/*Na função routine,
o tempo de comer (time_to_eat) é comparado com o 
tempo de morrer (time_to_die) para determinar se o filósofo 
// deve dormir após comer. A condição 
// philo->table->time_to_eat < philo->table->time_to_die 
// avalia se o tempo que um filósofo leva para comer 
// é menor que o tempo que ele pode sobreviver sem comer (tempo para morrer).
Situações ou casos em que o tempo de comer é menor que o tempo de morrer:
Configuração Inicial do Jogo: No início do jogo ou simulação,
os parâmetros time_to_eat e time_to_die são definidos. 
Se o time_to_eat for configurado para ser menor que o time_to_die,
essa condição será verdadeira. Isso pode ser uma decisão de 
design para garantir que os filósofos tenham tempo suficiente 
para realizar outras ações (como pensar ou dormir) antes de morrer de fome.
Dinâmica do Jogo: Durante a simulação,
essa condição garante que os filósofos só dormirão após 
comer se realmente tiverem tempo suficiente para realizar essa 
ação sem morrer de fome. Isso pode ajudar a simular um cenário 
mais realista onde as ações só são realizadas se houver 
tempo suficiente para elas.
Evitar Morte por Inanição: Se o tempo para comer for sempre 
menor que o tempo para morrer, isso pode ajudar a evitar que 
os filósofos morram de fome, pois eles terão tempo suficiente 
para comer e, em seguida, realizar outras ações, como dormir, 
antes de precisarem comer novamente.
Balanceamento do Jogo: Essa condição pode ser usada para 
balancear a simulação, garantindo que os filósofos tenham 
uma chance justa de sobreviver, realizando todas as suas 
ações necessárias em um ciclo de vida equilibrado (comer,
dormir, pensar).
Resumo do Comportamento da Condição:
Se Verdadeira: O filósofo dorme por um tempo calculado (time_pause_even),
que é determinado pelo seu id (par ou ímpar) e pelo time_to_eat,
mas apenas se o time_to_eat for menor que o time_to_die.
Se Falsa: O filósofo não dorme, pois o time_to_eat é maior que o time_to_die,
indicando que não há tempo suficiente para dormir 
sem correr o risco de morrer de fome.
Essa lógica ajuda a simular um cenário onde os filósofos 
devem balancear cuidadosamente suas ações para sobreviver,
considerando o tempo necessário para 
cada ação dentro do ciclo de vida de comer,
dormir e pensar.
*/
int	state_monitor(t_commonstruct *table)
{
	int			i;
	static int	satisfied_count;

	i = -1;
	while (++i < table->num_philos)
	{
		pthread_mutex_lock(&table->philo[i].mutex_state);
		if (table->philo[i].state == SATISFIED)
		{
			satisfied_count++;
			table->philo[i].state = DONE;
		}
		if (table->philo[i].state != DONE && get_time()
			- table->philo[i].last_meal_time > table->time_to_die)
		{
			pthread_mutex_lock(&table->mutex_dead);
			table->some_philo_died = 1;
			pthread_mutex_unlock(&table->mutex_dead);
			print_dead(&table->philo[i]);
			pthread_mutex_unlock(&table->philo[i].mutex_state);
			return (0);
		}
		pthread_mutex_unlock(&table->philo[i].mutex_state);
	}
	return (satisfied_count != table->num_philos);
}

// No return do if do while,
// podíamos guardar o retorno da função no segundo argumento,
// mas como não queremos, colocamos NULL. 
// Se a thread não for terminada,
// a função pthread_join retorna um valor diferente de 0,
// e se tal acontecer um erro é retornado. 
// O join junta a thread ao processo principal 
// (há duas formas de fazer isto: ou join ou detach. 
// join junta a thread ao processo principal,
// que espera que a thread termine para terminar também,
// dando free a todas as estruturas usadas. detach separa as threads,
// que correm em caminhos separados e ao mesmo tempo 
// e terminam quando tiverem que terminar,
// não esperando que o processo principal termine). 
// Nós escolhemos o join porque é mais fácil para depois 
// libertar a memória usada. Assim,
// se a thread não for terminada,
// a função pthread_join retorna um valor diferente de 0,
// e se tal acontecer um erro é retornado.
int	join_threads(t_commonstruct *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		if (pthread_join(table->philo[i].philo_thread, NULL))
			return (error_exit_msg("Failed to join thread\n", table,
					THREAD_ERROR));
	}
	return (0);
}

// Esta função cria as threads de cada filósofo e inicia a rotina 
// de cada filósofo. Se a função pthread_create falhar,
// a função retorna um erro.
int	start_threads(t_commonstruct *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (pthread_create(&table->philo[i].philo_thread, NULL, routine,
				&table->philo[i]))
			return (error_exit_msg("Thread creation failed\n", table,
					THREAD_ERROR));
		i++;
	}
	return (0);
}
