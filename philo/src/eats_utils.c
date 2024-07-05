/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eats_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:02:29 by joaosilva         #+#    #+#             */
/*   Updated: 2024/07/02 22:52:34 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Esta função serve para verificar se o filósofo
// morreu ou se ainda não morreu, já está satisfeito.
// Se o filósofo tiver morrido ou satisfeito, então a
// função retorna 1.
// Se ninguém morreu e o filósofo não está satisfeito,
// então a função retorna 0.
int	is_satisfied_or_dead(t_philo *philo)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&philo->commonstruct->mutex_dead);
	if (philo->commonstruct->some_philo_died)
		result = 1;
	pthread_mutex_unlock(&philo->commonstruct->mutex_dead);
	if (!result && philo->commonstruct->must_eat_times
		&& philo->n_meals_had == philo->commonstruct->must_eat_times)
	{
		pthread_mutex_lock(&philo->mutex_state);
		philo->state = SATISFIED;
		pthread_mutex_unlock(&philo->mutex_state);
		result = 1;
	}
	return (result);
}

// Esta função auxiliar da drop_forks é responsável
// por bloquear o mutex do garfo, marcar o garfo
// como não utilizado (0), e então desbloquear o mutex.
void	drop_fork(t_philo *philo, int fork_id)
{
	pthread_mutex_lock(&philo->commonstruct->mutex_forks[fork_id]);
	philo->commonstruct->taked_fork[fork_id] = 0;
	pthread_mutex_unlock(&philo->commonstruct->mutex_forks[fork_id]);
}

// A função drop_forks é chamada quando o filósofo termina de comer.
// É chamada na função eats e é responsável por largar os garfos.
// Primeiramente o garfo da esquerda é largado, e depois o garfo da direita.
void	drop_forks(t_philo *philo, int id)
{
	int	first_fork_id;
	int	second_fork_id;

	first_fork_id = id - 1;
	second_fork_id = id % philo->commonstruct->num_philos;
	drop_fork(philo, first_fork_id);
	drop_fork(philo, second_fork_id);
}

// Esta função é chamada quando o filósofo começa a comer,
// e é responsável por atualizar o tempo da última refeição.
// Como funciona? Primeiramente o mutex do estado do filósofo
//  é bloqueado, o estado do filósofo é atualizado para EATING
// (o que é feito na função print_state), e o mutex do estado do
// estado do filósofo é desbloqueado.
// Se estivermos no início da simulação, esse tempo é
// definido como o tempo de início da simulação. Onde?
// Na função init_philos. E porque é que é iniciaizado?
// Porque foi assim definido pelo programador, uma vez
// que no início da simulação, o filósofo ainda não comeu,
// e de acordo com a lógica do programa, ele tem de ter
// um tempo de última refeição. Porquê? Para que serve
// o tempo de última refeição?
// O tempo de última refeição é usado para verificar
// se um filósofo morreu de fome, o que é verificado
// na função state_monitor (através do 2º if do while:
// get_time() - table->philo[i].last_meal_time > table->time_to_die))
// Aqui exemplifica que se o tempo atual menos o tempo da última refeição
// (o last_meal_time) for maior que o tempo para morrer,
// então o filósofo morre.
// Se não estivermos no início da simulação, então o tempo
// da última refeição é atualizado para o tempo atual.
// Porquê? Porque o filósofo está a comer, e por isso,
// o tempo da última refeição é atualizado para o tempo
// atual.
void	update_last_meal_time(t_philo *philo, u_int64_t current_time)
{
	pthread_mutex_lock(&philo->mutex_state);
	philo->last_meal_time = current_time;
	pthread_mutex_unlock(&philo->mutex_state);
}

// Esta função é chamada quando o filósofo pega um garfo.
// Primeiramente tenta bloquear o mutex do garfo de forma a
// verificar se o garfo está disponível. Se o garfo estiver
// disponível, a função verifica se o filósofo está morto ou
// satisfeito. Se o filósofo estiver morto ou satisfeito,
// obviamente que não vai conseguir pegar no outro garfo e
// essa é a razão pela qual desbloqueamos o mutex do garfo
// mal entramos no while loop. Assim, se o filósofo estiver
// vivo, a função is_satisfied_or_dead irá retornar 0 e o
// filósofo poderá bloquear novamente o mutex do garfo.
// Se o filósofo não estiver morto ou satisfeito, então nunca
// conseguirá bloquear o mutex do garfo, deixando-o livre para
// outros filósofos pegarem.
void	pick_up_fork(t_philo *philo, int fork_id)
{
	pthread_mutex_lock(&philo->commonstruct->mutex_forks[fork_id]);
	while (philo->commonstruct->taked_fork[fork_id])
	{
		pthread_mutex_unlock(&philo->commonstruct->mutex_forks[fork_id]);
		is_satisfied_or_dead(philo);
		pthread_mutex_lock(&philo->commonstruct->mutex_forks[fork_id]);
	}
	philo->commonstruct->taked_fork[fork_id] = 1;
	pthread_mutex_unlock(&philo->commonstruct->mutex_forks[fork_id]);
	print_state(philo, TAKE_FORKS);
}
