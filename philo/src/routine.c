/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 12:30:17 by joaosilva         #+#    #+#             */
/*   Updated: 2024/07/03 00:08:02 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Esta função serve para definir o comportamento de um filósofo enquanto dorme.
static int	sleeps(t_philo *philo)
{
	u_int64_t	current_time;
	u_int64_t	time_start_sleeping;

	current_time = get_time();
	if (print_state(philo, SLEEPS))
	{
		time_start_sleeping = get_time() - current_time;
		usleep((philo->commonstruct->time_to_sleep - time_start_sleeping)
			* 1000);
	}
	return (!is_satisfied_or_dead(philo));
}

int	eats(t_philo *philo, int id)
{
	u_int64_t	current_time;
	u_int64_t	time_start_eating;

	pick_up_fork(philo, id - 1);
	pick_up_fork(philo, id % philo->commonstruct->num_philos);
	current_time = get_time();
	update_last_meal_time(philo, current_time);
	if (!is_satisfied_or_dead(philo) && print_state(philo, EATS))
	{
		time_start_eating = get_time() - current_time;
		usleep((philo->commonstruct->time_to_eat - time_start_eating) * 1000);
		if (philo->commonstruct->must_eat_times > 0)
			philo->n_meals_had++;
	}
	drop_forks(philo, id);
	return (!is_satisfied_or_dead(philo));
}

// Faz o mesmo que faz na função threads. Basicamente esta mutex wait
// assegura que todos os filósofos esperam uns pelos outros até
// todos terem as suas threads inicializadas. Se não houver este bloqueio,
// os filósofos podem começar a comer (dormir e pensar) antes de todos terem
//  as suas threads inicializadas. Assim, esperam todos uns pelos outros até
// todos terem as suas threads inicializadas. Esta mutex é essencial para tal.
// Desta forma, dentro do loop da função routine, todos os filósofos tentam
// bloquear a mutex wait. Se a mutex wait já estiver bloqueada (por exemplo na
// fase inicial pelo processo principal
// - podemos fazer a analogia com processo pai
// e processos filhos num fork), então o filósofo que vem a serguir não consegue
// bloquear a mutex wait e fica à espera que a mutex wait seja desbloqueada, o
// que apenas acontece quando o processo pai tiver terminado de criar todas as
// threads (que poderão ser equiparadas analogamente 
// a processos filhos num fork).
// Quando o processo pai termina de criar todas as threads, então aí sim,
// desbloqueia a mutex wait,permitindo que o filósofo que vem 
// a seguir (assumindo que estarão por ordem,
// será o segundo filósofo) bloqueie a mutex wait e assim 
// sucessivamente até que todos
void	wait_for_initialization(t_commonstruct *table)
{
	pthread_mutex_lock(&table->mutex_wait);
	pthread_mutex_unlock(&table->mutex_wait);
}

// Esta função serve para imprimir o status do filósofo, mas não só.
// É usada em várias outras funções, e numas é necessária
// para verificar se o filósofo morreu assim c/o pa imprimir o estado
// do filósofo caso este não tenha morrido. A função eats é a
// única que não precisa de verificar se o filósofo morreu,
// uma vez que a função eats já faz essa verificação através
// da função is_satisfied_or_dead.
// E então como funciona a print_state?
// Primeiro verifica se alguém morreu. Se alguém morrer já
// nem sequer vai verificar o resto, uma vez que não faz sentido
// imprimir o status de um filósofo que já morreu.
// Se já morreu de certeza que não vai comer, dormir ou pensar.
// Caso nínguém tenha morrido, então a função prossegue
// bloqueando a mutex print de forma a que mais nenhuma thread tenha
// acesso à variável print.
// E desta forma imprime o estado do filósofo (comer, dormir, pensar)
// apresentando o tempo decorrido desde o início do programa e
// o id do filósofo. Exemplo: 5 1 is eating, em que 5 é o tempo decorrido
// desde o início do programa, 1 é o id do filósofo e is eating é o estado.
// Por fim, desbloqueia a mutex print para que outras threads possam
// aceder à variável print após a thread atual ter terminado de usar a print.
// NOTA: A linha return (pthread_mutex_unlock(&philo->table->dead), 0); é
// um exemplo de como usar a vírgula para separar duas instruções em uma
// única linha. A primeira instrução é executada e o valor de retorno é
// descartado. A segunda instrução é então executada. A primeira instrução
// é usada para verificar se a função pthread_mutex_unlock foi bem-sucedida.
// Se não for bem-sucedida, a segunda instrução não será executada.
// Este tipo de retorno é comum em funções que retornam um valor de status.
int	print_state(t_philo *philo, char *state)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->commonstruct->mutex_dead);
	if (philo->commonstruct->some_philo_died)
		return (pthread_mutex_unlock(&philo->commonstruct->mutex_dead), 0);
	pthread_mutex_unlock(&philo->commonstruct->mutex_dead);
	pthread_mutex_lock(&philo->commonstruct->mutex_print);
	time = get_time() - philo->commonstruct->start_time;
	printf("%llu %d %s\n", time, philo->id, state);
	pthread_mutex_unlock(&philo->commonstruct->mutex_print);
	return (1);
}

// Esta função serve para definir o comportamento de um filósofo.
// Verifica primeiramente se estamos perante um jogo com apenas um filósofo.
// Se sim, então é printado que o filósofo apanhou um garfo. Contudo,
// não irá conseguir prosseguir com a simulação, uma vez que necessita
// dos 2 garfos para comer. Como só dispõe de um (porque a quantidade de
// garfos disponíveis está diretamente ligada ao número de filósofos
// presentes na simulação), então não conseguirá comer e morre.
// Se não estivermos perante um jogo com apenas um filósofo, então
// verifica se o id do filósofo NÂO é par. Se NÃO for par (sendo ímpar),
// então o filósofo dorme durante um tempo de pausa 
// que é igual ao tempo de comer.
// E porque é que isto é feito assim? Porque é necessário 
// estarem disponíveis 2 garfos
// por cada filósofo, e o número de garfos está diretamente ligado ao número
// de filósofos,
// e por isso tivemos que decidir quais iriam esperar até os garfos
// estarem novamente disponíveis. E porque esperam os filósofos com
// id ímpar? Esta foi uma decisão do programador. Podiam ter esperado os
// filósofos com id par. Contudo, o programador decidiu que os filósofos
// com id ímpar iriam esperar. Após esta decisão, um dos filósofos
// com id par começa por comer durante um período que é igual
// ao time_to_eat (proveniente do input do utilizador) menos o
// time_start_eating(que é igual ao tempo decorrido entre a entrada
// na função eats e a verificação do estado do filósofo que é realizada
// no primeiro if da função eats).
// O tempo de dormir é igual ao time_to_sleep 
// (proveniente do input do utilizador)
// menos o tempo decorrido desde o início do 
// sono (time_start_sleeping).
// O time_start_sleeping é igual ao tempo decorrido entre a entrada na função
// sleeps e a verificação do estado do filósofo que é realizada no primeiro if
// da função sleeps.
// E o tempo de pensar? O filósofo pensa durante quanto tempo? 
// O filósofo pensa durante o
// tempo que o programa está a correr. Se o programa começou 
// a ser executado às 10:00:00 e
// a função get_time() retornar 10:00:05,
// então o filósofo pensará durante 5 segundos.
// E porquê a decisão de pensar usando esta 
// fórmula de cálculo? Porque o filósofo pensa
// durante o tempo que o programa está a correr 
// porque durante esse tempo os outros filósofos
// estão a a fazer coisas: a comer ou a dormir. 
// Se o programa parar (pq um morreu ou já
// todos estão satisfeitos), o filósofo não pensa mais, logicamente.
// O programa termina se algum filósofo morrer ou se 
// todos os filósofos estiverem satisfeitos.
// O while loop da função routine termina 
// quando o filósofo deixa de comer (pq morreu é verificado
// dentro da função eats),
// deixa de dormir (pq morreu é 
// verificado dentro da função sleeps) ou deixa
// de pensar (pq morreu é verificado dentro da função print_state).
// Se o filósofo morrer,
// a função retorna NULL para indicar que a thread terminou sem retornar dados.
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->commonstruct->num_philos == 1)
		return (print_state(philo, TAKE_FORKS), NULL);
	if (!(philo->id % 2))
		usleep(philo->commonstruct->time_to_eat * 1000);
	while (1)
	{
		wait_for_initialization(philo->commonstruct);
		if (!eats(philo, philo->id))
			break ;
		if (!sleeps(philo))
			break ;
		if (!print_state(philo, THINKS))
			break ;
	}
	return (NULL);
}
