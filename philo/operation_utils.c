#include "philo.h"

void	no_synchro(t_philo *philo)
{
	if (philo->table->nbr_philo % 2 == 0)
	{
		if (philo->x % 2 == 0)
		{
			//ft_thread_timing(30);
			precise_usleep(30, philo->table);
		}
	}
	else
	{
		if (philo->x % 2 == 0)
		{
			ft_think(philo, 1);
		}
	}
}

int	ft_thread_synchro(t_mutex *mtx, long *t_nbr, long p_nbr)
{
	int	i;

	i = 0;
	pthread_mutex_lock(mtx);
	if (*t_nbr == p_nbr)
		i = 1;
	pthread_mutex_unlock(mtx);
	return (i);
}

long	ft_no_race_argcheck1(long *a, t_mutex *mtx)
{
	long	i;

	pthread_mutex_lock(mtx);
	i = *a;
	pthread_mutex_unlock(mtx);
	return (i);
}

int	ft_no_race_argcheck(int *a, t_mutex *mtx)
{
	int	i;

	pthread_mutex_lock(mtx);
	i = *a;
	pthread_mutex_unlock(mtx);
	return (i);
}

void	*ft_single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!ft_no_race_argcheck(&philo->table->start_threads_same_time,
			&philo->table->table_lock))
		;
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_eat_time = ft_take_time();
	pthread_mutex_unlock(&philo->philo_lock);
	pthread_mutex_lock(&philo->table->table_lock);
	philo->table->synchro_run_nbr++;
	pthread_mutex_unlock(&philo->table->table_lock);
	ft_write_state_change(LEFT_HAND, philo);
	while (!ft_no_race_argcheck(&philo->table->done, &philo->table->table_lock))
		usleep(100);
	return (NULL);
}