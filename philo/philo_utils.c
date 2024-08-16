/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:11:50 by abolor-e          #+#    #+#             */
/*   Updated: 2024/08/16 18:58:29 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
}

int	ft_thread_timing(long time)
{
	long	current_time;

	current_time = ft_take_time();
	while (ft_take_time() - current_time < time)
	{
		usleep(100);
	}
	return (SUCCESS);
}

long	ft_take_time(void)
{
	struct timeval	time;
	
	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
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

void	ft_error_str(char *str)
{
	printf("%s\n", str);
}
