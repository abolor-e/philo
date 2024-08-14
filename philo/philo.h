/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:11:41 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/14 20:03:20 by abolor-e         ###   ########.fr       */
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

typedef struct s_table t_table;
typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
	int		f_id;
	t_mutex	fork;
}				t_fork;

typedef struct s_philo
{
	pthread_t	tid;
	int			x;
	t_table		*table;
}				t_philo;

typedef struct s_table
{
	long	nbr_philo;
	long	tt_die;
	long	tt_eat;
	long	tt_sleep;
	long	philo_must_eat_nbr;
	t_fork	*f;
	t_philo	*p;
}				t_table;

long		ft_atol(const char *str);
int			ft_parse_init(int ac, char **av);
int			ft_parse_input5(t_table *table, char **av);
int			ft_parse_input6(t_table *table, char **av);
long		ft_take_time(void);
int			ft_thread_timing(long time);
void		ft_error_str(char *str);

#endif