/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:11:41 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/13 18:28:16 by abolor-e         ###   ########.fr       */
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

typedef struct s_argument_count
{
	long	nbr_philo;
	long	tt_die;
	long	tt_eat;
	long	tt_sleep;
	long	philo_must_eat_nbr;
}				t_argc;

long	ft_atol(const char *str);
t_argc	*ft_init_argument_check(int ac, char **av);

#endif
