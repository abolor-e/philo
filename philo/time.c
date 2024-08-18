#include "philo.h"

void	precise_usleep(long time, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;
	
	start = ft_take_time();
	while (ft_take_time() - start < time)
	{
		if (ft_no_race_argcheck(&table->done, &table->table_lock) == 1)
			break ;
		elapsed = ft_take_time() - start;
		rem = time - elapsed;
		
		if (rem > 1)
			ft_sleep(table, rem / 2);
		//usleep(rem / 2);
		else
		{
			while (ft_take_time() - start < time)
				;
		}
	}
}

void	ft_sleep(t_table *table, long time)
{
	long	wake_up;
	
	wake_up = ft_take_time() - ft_no_race_argcheck1(&table->start_time, &table->table_lock) + time;
	while (ft_no_race_argcheck(&table->done, &table->table_lock) == 0)
	{
		if (ft_take_time() - ft_no_race_argcheck1(&table->start_time, &table->table_lock) >= wake_up)
			break ;
		usleep(2 * table->nbr_philo);
	}
}

long	ft_take_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}