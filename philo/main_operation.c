/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:38:04 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/18 20:40:41 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"	

static void	ft_routine_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	ft_write_state_change(LEFT_HAND, philo);
	pthread_mutex_lock(&philo->right_fork->fork);
	ft_write_state_change(RIGHT_HAND, philo);
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_eat_time = ft_take_time();
	pthread_mutex_unlock(&philo->philo_lock);
	pthread_mutex_lock(&philo->philo_lock);
	philo->meal_counter++;
	pthread_mutex_unlock(&philo->philo_lock);
	ft_write_state_change(EAT, philo);
	//ft_thread_timing(philo->table, philo->table->tt_eat);
	precise_usleep(philo->table->tt_eat, philo->table);
	if (philo->table->philo_must_eat_nbr == philo->meal_counter)
	{
		pthread_mutex_lock(&philo->philo_lock);
		philo->philo_full = 1;
		pthread_mutex_unlock(&philo->philo_lock);
	}
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (ft_no_race_argcheck(&philo->table->\
			start_threads_same_time, &philo->table->table_lock) == 0)
		;
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_eat_time = ft_take_time();
	pthread_mutex_unlock(&philo->philo_lock);
	pthread_mutex_lock(&philo->table->table_lock);
	philo->table->synchro_run_nbr++;
	pthread_mutex_unlock(&philo->table->table_lock);
	no_synchro(philo);
	while (ft_no_race_argcheck(&philo->table->done,
			&philo->table->table_lock) == 0)
	{
		if (philo->philo_full == 1)
			break ;
		ft_routine_eat(philo);
		ft_write_state_change(SLEEP, philo);
		//ft_thread_timing(philo->table, philo->table->tt_sleep);
		precise_usleep(philo->table->tt_sleep, philo->table);
		ft_think(philo, 0);
	}
	return (NULL);
}

static int	ft_die(t_philo *philo)
{
	long	time;
	long	i;

	if (ft_no_race_argcheck(&philo->philo_full, &philo->philo_lock))
		return (0);
	pthread_mutex_lock(&philo->philo_lock);
	i = philo->last_eat_time;
	pthread_mutex_unlock(&philo->philo_lock);
	time = ft_take_time() - i;
	if (time > philo->table->tt_die)
		return (1);
	return (0);
}

void	*ft_routine_monitor(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (ft_thread_synchro(&table->table_lock,
			&table->synchro_run_nbr, table->nbr_philo) == 0)
		;
	while (ft_no_race_argcheck(&table->done, &table->table_lock) == 0)
	{
		i = 0;
		while (i < table->nbr_philo && !ft_no_race_argcheck(&table->done,
				&table->table_lock))
		{
			if (ft_die(table->p + i) == 1)
			{
				pthread_mutex_lock(&table->table_lock);
				table->done = 1;
				pthread_mutex_unlock(&table->table_lock);
				ft_write_state_change(DEAD, table->p + i);
			}
			i++;
		}
	}
	return (NULL);
}

void	ft_main_operation(t_table *table)
{
	int	i;

	i = 0;
	if (table->nbr_philo == 1)
		pthread_create(&table->p[0].tid, NULL, ft_single_philo, &table->p[0]);
	else if (table->philo_must_eat_nbr == 0)
		return ;
	else
	{
		while (i < table->nbr_philo)
		{
			if (pthread_create(&table->p[i].tid, NULL,
					ft_routine, &table->p[i]) != 0)
			{
				printf("ERROR: thread creation error!!!");
				table->p[i].tid = 0;
			}
			i++;
		}
	}
	pthread_create(&table->table_monitor, NULL, ft_routine_monitor, table);
	pthread_mutex_lock(&table->table_lock);
	table->start_time = ft_take_time();
	pthread_mutex_unlock(&table->table_lock);
	pthread_mutex_lock(&table->table_lock);
	table->start_threads_same_time = 1;
	pthread_mutex_unlock(&table->table_lock);
	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_join(table->p[i].tid, NULL);
		i++;
	}
	pthread_mutex_lock(&table->table_lock);
	table->done = 1;
	pthread_mutex_unlock(&table->table_lock);
	pthread_join(table->table_monitor, NULL);
	return ;
}
