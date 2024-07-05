/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   XPTO.C                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:48:18 by joaosilva         #+#    #+#             */
/*   Updated: 2024/06/26 15:02:13 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


typedef struct s_philo
{
	SÃO INICIALIZADAS NO while int				id; // Balsa tem igual
	NÂO SÃO INICIALIZADAS? OU SÂO NO MALLOC DA STRUCT?? int				meals_had; // Balsa tem meal_count. WALTER TEM EAT_COUNT. É o número de refeições que cada filósofo comeu efetivamente até chegar ao valor de must_eat_times.
    NÂO SÃO INICIALIZADAS? OU SÂO NO MALLOC DA STRUCT??  int             state; // Balsa tem status
	// t_state			state; // Balsa usa int
	// pthread_mutex_t	*left_f; //Balsa não tem
	// pthread_mutex_t	*right_f; //Balsa não tem
	JAM INICIA THREAD, BALSA E WALTER NÃO pthread_t		*philo_thread; // ??? Balsa tem, mas na struct philo. ISTO SERVE PARA GUARDAR AS THREADS DOS FILOSOFOS. PARA QUÊ? PARA PODER DAR JOIN NAS THREADS DOS FILOSOFOS.
	// para substituir a da linha de cima: pthread_t		thread; // Cada filósofo tem a sua própria thread. Ou seja, cada filósofo é um processo independente. 
    INIT_MUTEXES BALSA TEM AQUI, JAM TEM NA COMMONSTRUCT pthread_mutex_t	mutex_state; // Balsa tem status_mutex
    // Balsa tem int status e pthread_mutex_t status_mutex
	//pthread_mutex_t	mut_nb_meals_had; // Balsa não tem
	//pthread_mutex_t	mut_last_eat_time; // Balsa não tem
	SÃO INICIALIZADAS NO while u_int64_t		last_meal_time; // Balsa tem mas em susesconds_t last_meal suseconds_t		last_meal;
    SÃO INICIALIZADAS NO while struct s_commonstruct	*commonstruct; // Balsa tem mas nao como  struct s_data	*data; mas sim como struct s_table	*table;
}           t_philo;

typedef struct s_commonstruct
{
	ARG int				num_philos; // CHECK - Número de filósofos
	ARG int				must_eat_times; //  Balsa tem n_meals. CHECK - Num. vezes que cada filósofo deve comer se houver arg6/argv5.
	MALLOC int             *taked_fork; // Balsa tem fork_taken
    NÂO É INICIALIZADA int             some_philo_died; // Balsa tem someone_died
    //int				nb_full_p; // RETIRAR ??? REFERE-SE AOS FILÓSOFOS QUE JÁ ESTÃO SATISFEITOS
	//bool			keep_iterating; // RETIRAR
	ARG u_int64_t		time_to_eat; // CHECK - Tempo que um filósofo tem para comer
	ARG u_int64_t		time_to_die; // CHECK - Tempo que um filósofo tem para morrer
	ARG u_int64_t		time_to_sleep; // CHECK - Tempo que um filósofo tem para dormir
	WALTER INICIA START_TIME u_int64_t		start_time; // CHECK - Tempo de início do programa
	// pthread_mutex_t	mut_eat_t; // ???
	INIT_MUTEXES pthread_mutex_t	mutex_dead; // Balsa tem dead. ???Em vez desta Balsa tem dead e someone_died.
    	//Balsa// Qual a diferença entre someone_died e dead? A diferença entre someone_died e dead no contexto de um programa que utiliza threads, como uma simulação do problema dos filósofos jantando, reside principalmente no tipo e na finalidade de cada um: 
	    //Balsa//1. someone_died: Este é um campo do tipo int. Ele é usado como uma variável de estado para indicar se algum filósofo morreu. No contexto do problema dos filósofos jantando, someone_died pode ser usado para sinalizar todas as threads (filósofos) para parar a execução assim que um filósofo morre. Por exemplo, se someone_died for 0, significa que nenhum filósofo morreu; se for 1, significa que pelo menos um filósofo morreu.
	    //Balsa//2. dead: Este é um pthread_mutex_t, que é um tipo de mutex (mutual exclusion) do POSIX Threads. Mutexes são usados para controlar o acesso a recursos compartilhados por múltiplas threads, evitando condições de corrida. No contexto dado, dead pode ser usado para proteger a variável someone_died ou qualquer outra variável/estado compartilhado que precise ser modificado de forma segura por múltiplas threads. Quando uma thread quer verificar ou modificar o estado de someone_died, ela primeiro bloqueia o mutex dead, realiza as operações necessárias, e então libera o mutex. Isso garante que as modificações sejam atômicas e evita inconsistências de dados.
	    //Balsa//Resumo: someone_died é uma variável de estado usada para indicar se um evento (a morte de um filósofo) ocorreu, enquanto dead é um mecanismo de sincronização (mutex) usado para garantir que as operações em variáveis compartilhadas, como someone_died, sejam realizadas de maneira segura em um ambiente multithreaded.
	//Balsa int				someone_died; // Serve para indicar que um filósofo morreu.
	//Balsa pthread_mutex_t	dead; // Se um filósofo morrer, é necessário que os outros filósofos saibam que um filósofo morreu. E por isso, é necessário bloquear o mutex dead para que apenas um filósofo possa aceder ao valor de someone_died de cada vez.
	
	//pthread_mutex_t	mut_sleep_t; // ???
	INIT_MUTEXES pthread_mutex_t mutex_print; // Balsa tem print.
	//pthread_mutex_t	mut_nb_philos; // ???
	//pthread_mutex_t	mut_keep_iter; // ???
	//pthread_mutex_t	mut_start_time; // ???
	//pthread_t		monit_all_alive; // ??? 
	//pthread_t		monit_all_full; // Balsa não tem
    MALLOC E INIT_MUTEXES pthread_mutex_t	*mutex_forks;
	MALLOC t_philo			*philo; //
	// ??? *fork_taken não existe
    //int				*fork_taken;
	// dead e someone_died não existem
	
	
}           t_commonstruct;