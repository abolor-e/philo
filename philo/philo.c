/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:11:32 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/17 16:09:59 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	*routine(void *arg)
// {
// 	(void)arg;
// 	printf("hello\n");
// 	return (NULL);
// }

// int	ft_thread_creation(t_input *arg)
// {
// 	pthread_t	tid[200];
// 	int			i;

// 	i = 1;
// 	while (arg->nbr_philo != 0)
// 	{
// 		if (pthread_create(tid + i, NULL, routine, NULL) != SUCCESS)
// 		{
// 			write(2, "ft_thread_creation() error\n", 27);
// 			return (ERROR);
// 		}	
// 		i++;
// 		arg->nbr_philo--;
// 	}
// 	while (i > 1)
// 	{
// 		if (pthread_join(tid[i - 1], NULL) != SUCCESS)
// 		{
// 			write(2, "thread_join error\n", 18);
// 			return (ERROR);
// 		}
// 		i--;
// 	}
// 	return (SUCCESS);
// }

int	main(int ac, char **av)
{
	t_table	table;
	
	if (ac == 5 || ac == 6)
	{
		if (ft_parse_init(&table, ac, av) == ERROR)
			return (ERROR);
		ft_main_operation(&table);
		ft_free(&table);
	}
	else
		return (ft_error_str(MSG5), ERROR);
}
