/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:33:35 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/14 20:03:44 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parse_input6(t_table *table, char **av)
{
	table->nbr_philo = ft_atol(av[1]);
	table->tt_die = ft_atol(av[2]);
	table->tt_eat = ft_atol(av[3]);
	table->tt_sleep = ft_atol(av[4]);
	table->philo_must_eat_nbr = ft_atol(av[5]);
	if (!table->nbr_philo || !table->tt_die || !table->tt_eat
		|| !table->tt_sleep)
		return (ft_error_str(MSG2), ERROR);
	else if (table->nbr_philo > INT_MAX || table->nbr_philo < 0
		|| table->tt_die > INT_MAX || table->tt_die < 0
		|| table->tt_eat > INT_MAX || table->tt_eat < 0
		|| table->tt_sleep > INT_MAX || table->tt_sleep < 0
		|| table->philo_must_eat_nbr > INT_MAX
		|| table->philo_must_eat_nbr < 0)
		return (ft_error_str(MSG1), ERROR);
	return (SUCCESS);
}

int	ft_parse_input5(t_table *table, char **av)
{
	table->nbr_philo = ft_atol(av[1]);
	table->tt_die = ft_atol(av[2]);
	table->tt_eat = ft_atol(av[3]);
	table->tt_sleep = ft_atol(av[4]);
	table->philo_must_eat_nbr = -1;
	if (!table->nbr_philo || !table->tt_die || !table->tt_eat
		|| !table->tt_sleep)
		return (ft_error_str(MSG2), ERROR);
	else if (table->nbr_philo > INT_MAX || table->nbr_philo < 0
		|| table->tt_die > INT_MAX || table->tt_die < 0
		|| table->tt_eat > INT_MAX || table->tt_eat < 0
		|| table->tt_sleep > INT_MAX || table->tt_sleep < 0)
		return (ft_error_str(MSG1), ERROR);
	return (SUCCESS);
}

int	ft_parse_input(t_table *table, int ac, char **av)
{
	if (ac == 5)
	{
		if (ft_parse_input5(table, av) == ERROR)
			return (ft_error_str(MSG4), ERROR);
	}
	if (ac == 6)
	{
		if (ft_parse_input6(table, av) == ERROR)
			return (ft_error_str(MSG3), ERROR);
	}
	return (SUCCESS);
}

void	ft_init_fork(t_table *table)
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

void	ft_init_philo(t_table *table)
{
	int		i;
	t_philo	*philo;
	
	i = 0;
	while (i < table->nbr_philo)
	{
		philo = table->p + i;
		philo->tid = i + 1;
		philo->table = table;

		
	}
}

int	ft_parse_init(int ac, char **av)
{
	t_table	table;

	if (ft_parse_input(&table, ac, av) == ERROR)
		return (ERROR);
	table.p = malloc(sizeof(t_philo) * table.nbr_philo);
	if (!table.p)
		return (ft_error_str(MSG6), ERROR);
	table.f = malloc(sizeof(t_fork) * table.nbr_philo);
	if (!table.f)
		return (ft_error_str(MSG7), ERROR);
	ft_init_fork(&table);
	ft_init_philo(&table);
	// printf("table input nbr philo: %ld\n", table.nbr_philo);
	// printf("table input time tdie: %ld\n", table.tt_die);
	// printf("table input time teat: %ld\n", table.tt_eat);
	// printf("table input t t sleep: %ld\n", table.tt_sleep);
	// printf("table input must eat : %ld\n", table.philo_must_eat_nbr);
	return (SUCCESS);
}
