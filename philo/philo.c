/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:11:32 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/18 15:11:56 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_init_fork(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nbr_philo)
	{
		pthread_mutex_init(&table->f[i].fork, NULL);
		table->f[i].f_id = i;
		i++;
	}
}

static void	ft_init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->nbr_philo)
	{
		philo = table->p + i;
		philo->x = i + 1;
		philo->table = table;
		philo->meal_counter = 0;
		philo->philo_full = 0;
		pthread_mutex_init(&philo->philo_lock, NULL);
		philo->left_fork = &table->f[philo->x - 1];
		philo->right_fork = &table->f[philo->x % table->nbr_philo];
		if (philo->x % 2 == 0)
		{
			philo->right_fork = &table->f[philo->x - 1];
			philo->left_fork = &table->f[philo->x % table->nbr_philo];
		}
		i++;
	}
}

int	ft_parse_init(t_table *table, int ac, char **av)
{
	int	i;

	i = 0;
	if (ft_parse_input(table, ac, av) == ERROR)
		return (ERROR);
	table->start_threads_same_time = 0;
	table->done = 0;
	table->synchro_run_nbr = 0;
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->table_lock, NULL);
	table->p = malloc(sizeof(t_philo) * table->nbr_philo);
	if (!table->p)
		return (ft_error_str(MSG6), ERROR);
	table->f = malloc(sizeof(t_fork) * table->nbr_philo);
	if (!table->f)
		return (ft_error_str(MSG7), ERROR);
	ft_init_fork(table);
	ft_init_philo(table);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_table	table;
	
	if (ac == 5 || ac == 6)
	{
		if (ft_parse_init(&table, ac, av) == ERROR)
			return (ERROR);
		ft_main_operation(&table);
		ft_free(&table);
		return (SUCCESS);
	}
	else
		return (ft_error_str(MSG5), ERROR);
}
