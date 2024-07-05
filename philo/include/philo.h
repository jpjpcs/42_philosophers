/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaosilva <joaosilva@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 15:20:39 by joaosilva         #+#    #+#             */
/*   Updated: 2024/07/03 13:24:26 by joaosilva        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define INVALID_ARGS 0
# define MALLOC_ERROR 1
# define MUTEX_ERROR 2
# define THREAD_ERROR 3

# define TAKE_FORKS "has taken a fork"
# define EATS "is eating"
# define SLEEPS "is sleeping"
# define THINKS "is thinking"
# define DIED " died\n"

# define EAT 1
# define SLEEP 2

# define DONE 1
# define SATISFIED 2

// Escolha das mutexes:
/* A escolha de qual mutex usar em um programa multithread,
	como uma simulação do problema dos filósofos jantando,
	depende do recurso ou da variável que se deseja proteger para 
	evitar condições de corrida. No trecho de código fornecido,
	cada mutex definido com base em seus nomes e comentários:
// dead: Protege a variável someone_died ou qualquer outra 
variável/estado compartilhado que precise ser modificado de forma 
segura por múltiplas threads. É usada para garantir que a 
informação sobre a morte de um filósofo seja acessada 
e modificada de maneira atômica,
	evitando inconsistências.
// print: Garante que as mensagens de log (como timestamps) 
sejam impressas de forma sequencial,
	sem sobreposição,
	mantendo a legibilidade do log. É usada quando múltiplos
	filósofos tentam imprimir mensagens ao mesmo tempo.
// forks: Um array de mutexes,
	cada um protegendo o acesso a um garfo específico. 
	Isso evita que dois filósofos peguem o mesmo garfo ao mesmo tempo,
	o que é essencial para evitar deadlock e garantir que cada filósofo 
	possa comer quando tiver acesso a dois garfos.
// A escolha de qual mutex usar depende do contexto específico e do 
recurso que está sendo acessado ou modificado. Por exemplo:
// Se estamos modificando a variável someone_died, você usaria o mutex dead.
// Se estamos imprimindo logs, usaria o mutex print.
// Se estamos acessando um garfo, usaria o mutex correspondente no array forks.
*/

typedef struct s_philo
{
	int						id;
	int						n_meals_had;
	int						state;
	pthread_t				philo_thread;
	pthread_mutex_t			mutex_state;
	u_int64_t				last_meal_time;
	struct s_commonstruct	*commonstruct;
}							t_philo;

typedef struct s_commonstruct
{
	int						num_philos;
	int						must_eat_times;
	int						*taked_fork; //optamos por colocar o taked_fork 
	// dentro da estrutura comum, uma vez que consideramos que os garfos são 
	// comuns a todos os philos. Ao fazê-lo temos algumas desvantagens e 
	// requisitos. Como requisitos, temos de fazê-lo como ponteiro
	// pq não sabemos qts vamos ter (uma vez q estão associados ao nº philos.
	// E como não sabemos a qtdade inicial, temos sempre de fazer malloc.
	// As desvantagens é que assim temos de fazer vários mallocs (na função
	// init_callocs) e não somente um (como seria se tivessemos dentro da 
	// struct philo. Se só tivessemos dentro dessa struct, o taked_fork seria
	// inicializado quando fazemos calloc à struct philo).
	int						some_philo_died;
	u_int64_t				time_to_eat;
	u_int64_t				time_to_die;
	u_int64_t				time_to_sleep;
	u_int64_t				start_time;	// tempo de início da simulação
	pthread_mutex_t			mutex_dead;	// mutex da variável some_philo_died
	pthread_mutex_t			mutex_wait;	// esta mutex serve para verificar se 
	//todos os filósofos já foram inicializados.	
	pthread_mutex_t			mutex_print;	// mutex da variável print
	pthread_mutex_t			*mutex_forks;	// mutex da variável taked_fork
	// no mesmo sentido do int fork, podíamos ter colocado o mutex_forks
	// dentro da struct philo. No entanto, optamos por colocar na struct
	// comum, uma vez que consideramos que os garfos são comuns a 
	// todos os philos.
	// Os requisitos e desvantagens são as mesmas que para o taked_fork.
	struct s_philo			*philo;
}							t_commonstruct;

// init_philosophers_program
int							init_args(t_commonstruct *table, int argc,
								char **argv);
int							init_callocs(t_commonstruct *table);
int							init_mutexes_and_forks(t_commonstruct *table);
int							init_philo(t_commonstruct *table);

// threads
int							start_threads(t_commonstruct *table);
int							join_threads(t_commonstruct *table);
int							state_monitor(t_commonstruct *table);

// routine.c
void						*routine(void *arg);
int							print_state(t_philo *philo, char *status);

// eats_utils
void						pick_up_fork(t_philo *philo, int fork_id);
void						update_last_meal_time(t_philo *philo,
								u_int64_t current_time);
void						drop_forks(t_philo *philo, int id);
int							is_satisfied_or_dead(t_philo *philo);

// error_free.c
int							error_exit_msg(char *msg, t_commonstruct *table,
								int n);
void						destroy_mutexes(t_commonstruct *table);
void						free_callocs(t_commonstruct *table);

// utils.c
int							ft_atoi(const char *str);
int							ft_is_number(int argc, char **argv);
void						*ft_calloc(size_t nmemb, size_t size);
u_int64_t					get_time(void);

#endif