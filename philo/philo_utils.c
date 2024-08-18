/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:11:50 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/18 20:43:20 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_write_state_change(t_state_c state, t_philo *philo)
{
	long	i;

	if (philo->philo_full == 1)
		return ;
	pthread_mutex_lock(&philo->table->write_lock);
	i = ft_take_time() - philo->table->start_time;
	if (ft_no_race_argcheck(&philo->table->done,
			&philo->table->table_lock) == 0)
	{
		if (state == SLEEP)
			printf("%ld %d is sleeping\n", i, philo->x);
		else if (state == EAT)
			printf("%ld %d is eating\n", i, philo->x);
		else if (state == THINK)
			printf("%ld %d is thinking\n", i, philo->x);
		else if (state == LEFT_HAND)
			printf("%ld %d has taken a fork\n", i, philo->x);
		else if (state == RIGHT_HAND)
			printf("%ld %d has taken a fork\n", i, philo->x);
	}
	else if (state == DEAD)
		printf("%ld %d died\n", i, philo->x);
	pthread_mutex_unlock(&philo->table->write_lock);
}

void	ft_free(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_destroy(&table->p->philo_lock);
		i++;
	}
	pthread_mutex_destroy(&table->table_lock);
	pthread_mutex_destroy(&table->write_lock);
	free(table->p);
	free(table->f);
	return ;
}

int	ft_thread_timing(t_table *table, long time)
{
	long	current_time;

	current_time = ft_take_time();
	while (ft_take_time() - current_time < time)
	{
		//usleep(5);
		ft_sleep(table, 1 / 1000);
	}
	return (SUCCESS);
}

long	ft_atol(const char *str)
{
	int		i;
	long	s;
	long	res;

	s = 1;
	i = 0;
	res = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == ' '
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * s);
}

void	ft_think(t_philo *philo, int i)
{
	long	teat;
	long	tsleep;
	long	tthink;

	if (!i)
		ft_write_state_change(THINK, philo);
	if (philo->table->nbr_philo % 2 == 0)
		return ;
	teat = philo->table->tt_eat;
	tsleep = philo->table->tt_sleep;
	tthink = teat * 2 - tsleep;
	if (tthink < 0)
		tthink = 0;
	precise_usleep(tthink * 0.42, philo->table);
	// ft_thread_timing(tthink * 0.45);
 	precise_usleep(tthink * 0.4, philo->table);
}
