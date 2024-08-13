/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:11:32 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/13 18:31:46 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_argc	*ft_init_argument_check(int ac, char **av)
{
	t_argc	*argc;

	argc = (t_argc *)malloc(sizeof(*argc));//Do not forget to free malloc!
	if (!argc)
		return (NULL);
	argc->nbr_philo = ft_atol(av[1]);
	argc->tt_die = ft_atol(av[2]);
	argc->tt_eat = ft_atol(av[3]);
	argc->tt_sleep = ft_atol(av[4]);
	if (ac == 6)
		argc->philo_must_eat_nbr = ft_atol(av[5]);
	if (!argc->nbr_philo || !argc->tt_die || !argc->tt_eat || !argc->tt_sleep)
		return (NULL);
	else if (argc->nbr_philo > INT_MAX || argc->nbr_philo < INT_MIN
		|| argc->tt_die > INT_MAX || argc->tt_die < INT_MIN
		|| argc->tt_eat > INT_MAX || argc->tt_eat < INT_MIN
		|| argc->tt_sleep > INT_MAX || argc->tt_sleep < INT_MIN)
		return (NULL);
	else
		return (argc);
}

int	main(int ac, char **av)
{
	t_argc	*arg;

	if (ac == 5 || ac == 6)
	{
		arg = ft_init_argument_check(ac, av);
		if (arg == NULL)
		{
			free(arg);
			return (ERROR);
		}
		
	}
	else
	{
		write(2, "check argument number\n", 22);
		return (ERROR);
	}
}
