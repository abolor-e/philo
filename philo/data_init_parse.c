/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:33:35 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/18 13:52:37 by abolor-e         ###   ########.fr       */
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
		|| !table->tt_sleep || !table->philo_must_eat_nbr)
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



