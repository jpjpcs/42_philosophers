/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:58:34 by joaosilva         #+#    #+#             */
/*   Updated: 2024/07/03 00:03:39 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// Definições gerais:
// 1. O que é DEADLOCK? Deadlock é uma situação em que dois ou mais
// processos ficam bloqueados indefinidamente, esperando uns pelos
// outros para liberar recursos. Isso pode ocorrer quando dois
// processos estão esperando por um recurso que o outro processo
// tem e não pode liberar. Por exemplo, se um processo A está
// esperando por um recurso que o processo B tem e o processo B
// está esperando por um recurso que o processo A tem, então
// ambos os processos ficarão bloqueados indefinidamente,
// esperando que o outro libere o recurso que precisa.
// 2. O que é MUTEX? Mutex é uma abreviação de exclusão mútua.
// É um mecanismo de sincronização que é usado para garantir
// que apenas um thread possa acessar um recurso compartilhado
// por vez. Isso é feito bloqueando o recurso com um mutex
// antes de acessá-lo e desbloqueando-o após o acesso.
// 3. O que é THREAD? Uma thread é uma unidade de execução
// dentro de um processo. Um processo pode ter várias threads
// que são executadas em paralelo. Cada thread tem seu próprio
// conjunto de registros, pilha e contador de programa, mas
// compartilha o mesmo espaço de endereço e recursos com
// outras threads no mesmo processo.
// 4. O que é DATARACE? Uma condição de corrida é um problema
// que ocorre em um sistema de computador quando dois ou
// mais threads ou processos concorrentes tentam acessar
// um recurso compartilhado ao mesmo tempo e o resultado
// da operação depende da ordem de acesso. Isso pode levar
// a resultados inesperados ou indefinidos, como corrupção
// de dados ou falhas no sistema.

void	free_commonstruct(t_commonstruct *table)
{
	destroy_mutexes(table);
	free_callocs(table);
}

// Resumindo, esta função cria uma thread para cada filósofo,
// bloqueia o mutex wait e
// inicia a monitorização (que verifica se os filósofos 
// já estão TODOS satisfeitos ou
// se algum morreu. Se os filósofos estiverem satisfeitos 
// ou se algum filosofo morreu,
// a função retorna 0 e termina o programa. Caso contrário, 
// se os filósofos não
// estiverem satisfeitos (então o valor de satisfied_count 
// é diferente de table->n_philos(),
// logo a função retorna 1 e o ciclo while continua a correr.
// No seu início a função bloqueia o mutex wait. E porquê? 
// Para que os filósofos esperem uns pelos outros até 
// todos terem as suas threads inicializadas.
// Se não houver este bloqueio, os filósofos podem 
// começar a comer (dormir/pensar) antes de
// todos terem as suas threads inicializadas. Assim,
//esperam todos uns pelos outros até
// todos terem as suas threads inicializadas. Esta mutex 
// é essencial para isso. E como é
// que é essencial? Porque o processo principal 
// (semelhante ao processo pai num fork) bloqueia a mutex wait,
//e só a desbloqueia após a inicialização de TODAS as threads. 
// Só apos a inicialização de todas as threads é que o 
// processo principal desbloqueia a mutex wait.
// E como é que o filósofo que vem a seguir 
// (presume-se o segundo se o programa seguir a ordem
// prevista) consegue saber que a mutex wait está bloqueada? 
// Porque funciona "como um while" - o filósofo que vem a seguir 
// (presume-se o segundo se o programa seguir a ordem prevista) já
// estava à espera que a mutex wait fosse desbloqueada? Onde? 
// Na função routine (que é chamada dentro da função 
// start_threads(que é chamada nesta função).
// Esta mutex wait é também usada na tal função routine 
// (que verifica a rotina dos filósofos: comer, dormir, pensar,
// e esta função routine é chamada dentro da função start_threads),
// tendo exatamente a mesma função que tem aqui.
// Após a inicialização das threads, a mutex wait é desbloqueada nesta função
// pelo "processo principal" (semelhante ao "processo pai" num fork) - esta
// explicação é abordada com maior profundidade na função 
// wait_for_initialization (que é chamada dentro da função r
// outine presente no ficheiro routine.c).
// Após inicializar todas as threads, correr a rotina de cada um, 
// a função threads atualiza o tempo de início do programa 
// (que foi atribuído a primeira vez na função init_philo, chamada 
// na função init_philosophers_program,chamada no main).
// E porque é que o tempo de início do programa é chamado a 
// primeira vez na função init_philo? Porque cada filósofo tem 
// um tempo de última refeição (last_meal_time)
// que na fase inicial do programa deverá ser igual 
// ao tempo de início do programa. E porquê? Porque irá ser 
// usado no segundo if da função monitor (presente no
// ficheiro threads.c) para verificar se o tempo atual 
// menos o último tempo em que o filósofo comeu é maior 
// que o tempo para morrer (time_to_die proveniente do
// input do user). Se for, então o filósofo 
// i morreu (condição do if: get_time() - table->philo[i].last_meal_time 
// > table->time_to_die)).
// A função state_monitor verifica se algum filósofo morreu. 
// Enquanto monitor retornar 1,
// o ciclo while continua a correr. Se nenhum filósofo morreu,
// state_monitor retorna 1.
// Se algum filósofo morreu, state_monitor retorna 0.
// Finalmente temos a função join_threads que é 
// chamada nesta função threads,
// e que serve para esperar que todas as threads terminem.
// O join junta a thread ao processo principal 
// (há duas formas de fazer isto:
// ou join ou detach. join junta a thread ao 
// processo principal, que espera
// que a TODAS as threads terminem para terminar também, 
// dando free a todas as estruturas usadas. detach separa 
// as threads, que correm em caminhos
// separados e ao mesmo tempo, e terminam apenas 
// quando tiverem que terminar,
// não esperando que o processo principal termine). 
// Eu escolhi (e todos os outros
// programadores que fizeram este projeto) o 
// join porque é mais fácil
// para depois libertar a memória usada.
static int	threads(t_commonstruct *table)
{
	pthread_mutex_lock(&table->mutex_wait);
	if (start_threads(table))
		return (1);
	table->start_time = get_time();
	pthread_mutex_unlock(&table->mutex_wait);
	while (state_monitor(table))
		;
	if (join_threads(table))
		return (1);
	return (0);
}

// Esta função inicializa toda a estrutura commonstruct
// e a estrutura philo, que é um array de filósofos.
// A função init_philosophers_program é chamada no main,
// e preenche a estrutura commonstruct com os valores
// passados pelo utilizador, e chama as funções que
// inicializam os mutexes, os callocs, os filósofos e
// as threads. Se alguma destas funções retornar 1 (indicando
// que algo correu mal), a função init_philosophers_program
// retorna 1, e o programa termina.
static int	init_philosophers_program(t_commonstruct *table, int argc,
		char **argv)
{
	if (init_args(table, argc, argv))
		return (1);
	if (init_callocs(table))
		return (1);
	if (init_mutexes_and_forks(table))
		return (1);
	if (init_philo(table))
		return (1);
	return (0);
}

//  O número de filósofos tem se ser maior que 1 (tem
//  de haver pelo menos um filósofo) e menor que 200,
//  e os tempos (morrer, comer, pensar) deverão ser
// maiores que 60. Porquê? Pq está no subject. Este
// limite pode ser imposto para garantir que o programa
// tenha um comportamento previsível e para evitar
// condições de corrida ou deadlock que podem ser
// mais prováveis com tempos muito curtos.
// Se os tempos forem muito baixos, o overhead de
// gerenciamento de threads (ou processos) pode tornar-se
// significativo em relação ao trabalho real realizado,
// levando a um comportamento ineficiente. Além disso,
// tempos muito curtos podem não permitir que os filósofos
// completem suas ações adequadamente antes de serem interrompidos,
// o que poderia levar a situações onde filósofos "morrem de fome"
// ou o sistema fica em deadlock, especialmente em sistemas com
// agendamento de threads menos previsível.
// E o que é DEADLOCK? Deadlock é uma situação em que dois ou mais
// processos ficam bloqueados indefinidamente, esperando uns pelos
// outros para liberar recursos. Isso pode ocorrer quando dois
// processos estão esperando por um recurso que o outro processo
// tem e não pode liberar. Por exemplo, se um processo A está
// esperando por um recurso que o processo B tem e o processo B
// está esperando por um recurso que o processo A tem, então
// ambos os processos ficarão bloqueados indefinidamente,
// esperando que o outro libere o recurso que precisa.
int	check_args(t_commonstruct *table, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (error_exit_msg("\nWrong number of arguments.\n", table,
				INVALID_ARGS));
	if (ft_is_number(argc, argv))
		return (error_exit_msg("\nArguments must be numbers.\n", table,
				INVALID_ARGS));
	if ((ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		|| (ft_atoi(argv[2]) < 1 || ft_atoi(argv[2]) < 60)
		|| (ft_atoi(argv[3]) < 1 || ft_atoi(argv[3]) < 60)
		|| (ft_atoi(argv[4]) < 1 || ft_atoi(argv[4]) < 60) || (argc == 6
			&& ft_atoi(argv[5]) < 0))
		return (error_exit_msg("\nphilos between 1-200. Times > 60.\n",
				table, INVALID_ARGS));
	if (argc == 6 && ft_atoi(argv[5]) <= 0)
		return (error_exit_msg("\nNumber of meals must be greater than 0.\n",
				table, INVALID_ARGS));
	return (0);
}

// No main inicializamos toda a esturuta commonstruct,
// colocando todos os seus elementos a zero, e
// chamamos as funções que verificam os argumentos
// passados pelo utilizador, inicializam a estrutura
// commonstruct e philo, e chamamos as funções que
// criam as threads dos filósofos, e verificam se
// algum filósofo morreu ou se todos estão satisfeitos.
// Se alguma destas funções retornar 1, o programa
// termina. Se todas as funções retornarem 0, o programa
// termina sem erros. No final chamamos a função
// free_commonstruct para libertar a memória alocada e
// destruir os mutexes.
int	main(int argc, char **argv)
{
	t_commonstruct	table;

	table = (t_commonstruct){0};
	if (check_args(&table, argc, argv) || init_philosophers_program(&table,
			argc, argv) || threads(&table))
		return (1);
	free_commonstruct(&table);
	return (0);
}
