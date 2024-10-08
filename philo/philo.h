/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:11:41 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/18 20:37:02 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

# define ERROR 	-1
# define SUCCESS 0

# define MSG1	"Error: Found numbers higher than INT_MAX and\
					numbers that are negative!"
# define MSG2	"Error: Input/s cannot have value zero (0)!"
# define MSG3	"Error: When argument count is 6!"
# define MSG4	"Error: When argument count is 5!"
# define MSG5	"Error: Check argument number!"
# define MSG6	"Error: Philo malloc NULL!"
# define MSG7	"Error: Fork malloc NULL"

typedef struct s_table	t_table;
typedef pthread_mutex_t	t_mutex;

typedef enum e_state_changes
{
	SLEEP = 0,
	EAT,
	THINK,
	DEAD,
	RIGHT_HAND,
	LEFT_HAND
}			t_state_c;

typedef struct s_fork
{
	int		f_id;
	t_mutex	fork;
}				t_fork;

typedef struct s_philo
{
	pthread_t	tid;
	int			philo_full;
	t_mutex		philo_lock;
	int			x;
	int			meal_counter;
	long		last_eat_time;
	t_table		*table;
	t_fork		*right_fork;
	t_fork		*left_fork;
}				t_philo;

typedef struct s_table
{
	long		nbr_philo;
	long		tt_die;
	long		tt_eat;
	long		tt_sleep;
	long		philo_must_eat_nbr;
	long		start_time;
	int			start_threads_same_time;
	int			done;
	long		synchro_run_nbr;
	pthread_t	table_monitor;
	t_mutex		table_lock;
	t_mutex		write_lock;
	t_fork		*f;
	t_philo		*p;
}				t_table;

int		ft_parse_input(t_table *table, int ac, char **av);
long	ft_atol(const char *str);
int		ft_parse_init(t_table *table, int ac, char **av);
int		ft_parse_input5(t_table *table, char **av);
int		ft_parse_input6(t_table *table, char **av);
long	ft_take_time(void);
int		ft_thread_timing(t_table *table, long time);
void	ft_error_str(char *str);
//void	ft_init_philo(t_table *table);
//void	ft_init_fork(t_table *table);
int		ft_no_race_argcheck(int *a, t_mutex *mtx);
void	ft_write_state_change(t_state_c state, t_philo *philo);
void	*ft_routine(void *arg);
void	*ft_routine_monitor(void *arg);
void	*ft_single_philo(void *arg);
void	ft_think(t_philo *philo, int i);
 void	no_synchro(t_philo *philo);
void	ft_main_operation(t_table *table);
void	ft_free(t_table *table);
int		ft_thread_synchro(t_mutex *mtx, long *t_nbr, long p_nbr);

void	precise_usleep(long time, t_table *table);

void	ft_sleep(t_table *table, long time);
long	ft_no_race_argcheck1(long *a, t_mutex *mtx);
#endif