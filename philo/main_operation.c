#include "philo.h"	

int	ft_no_race_argcheck(int *a, t_mutex *mtx)
{
	int	i;

	pthread_mutex_lock(mtx);
	i = *a;
	pthread_mutex_unlock(mtx);
	return (i);
}

void	ft_write_state_change(t_state_c state, t_philo *philo)
{
	long	i;

	if (philo->philo_full == 1)
		return ;
	pthread_mutex_lock(&philo->table->write_lock);
	i = ft_take_time() - philo->table->start_time; 
	if (ft_no_race_argcheck(&philo->table->done, &philo->table->table_lock) == 0)
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

static void	ft_routine_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork);
	pthread_mutex_lock(&philo->right_fork->fork);
	ft_write_state_change(LEFT_HAND, philo);
	ft_write_state_change(RIGHT_HAND, philo);

	pthread_mutex_lock(&philo->philo_lock);
	philo->last_eat_time = ft_take_time();
	pthread_mutex_unlock(&philo->philo_lock);

	philo->meal_counter++;
	ft_write_state_change(EAT, philo);
	ft_thread_timing(philo->table->tt_eat);
	if (philo->table->philo_must_eat_nbr == philo->meal_counter)
	{
		pthread_mutex_lock(&philo->philo_lock);
		philo->philo_full = 1;
		pthread_mutex_unlock(&philo->philo_lock);
	}
	pthread_mutex_unlock(&philo->left_fork->fork);
	pthread_mutex_unlock(&philo->right_fork->fork);
}

void ft_think(t_philo *philo, int i)
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
	ft_thread_timing(tthink * 0.42);
}

void	no_synchro(t_philo *philo)
{
	if (philo->table->nbr_philo % 2 == 0)
	{
		if (philo->x % 2 == 0)
		{
			ft_thread_timing(3e4);
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

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (ft_no_race_argcheck(&philo->table->start_threads_same_time, &philo->table->table_lock) == 0)
		;
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_eat_time = ft_take_time();
	pthread_mutex_unlock(&philo->philo_lock);

	pthread_mutex_lock(&philo->table->table_lock);
	philo->table->synchro_run_nbr++;
	pthread_mutex_unlock(&philo->table->table_lock);

	no_synchro(philo);

	while (ft_no_race_argcheck(&philo->table->done, &philo->table->table_lock) == 0)
	{
		//am i full
		if (philo->philo_full == 1)
			break ;
		//eat
		ft_routine_eat(philo);
		//sleep
		ft_write_state_change(SLEEP, philo);
		ft_thread_timing(philo->table->tt_sleep);
		//think
		ft_think(philo, 0);
		//ft_write_state_change(THINK, philo);
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
	int	i;

	table = (t_table *)arg;
	while (ft_thread_synchro(&table->table_lock, &table->synchro_run_nbr, table->nbr_philo) == 0)
		;
	while (ft_no_race_argcheck(&table->done, &table->table_lock) == 0)
	{
		i = 0;
		while (i < table->nbr_philo && !ft_no_race_argcheck(&table->done, &table->table_lock))
		{
			if (ft_die(table->p + i) == 1)
			{
				pthread_mutex_lock(&table->table_lock);
				table->done = 1;
				pthread_mutex_unlock(&table->table_lock);
				ft_write_state_change(DEAD, table->p);
			}
		}
	}
	return (NULL);
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

void	*ft_single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!ft_no_race_argcheck(&philo->table->start_threads_same_time, &philo->table->table_lock))
		;
	pthread_mutex_lock(&philo->philo_lock);
	philo->last_eat_time = ft_take_time();
	pthread_mutex_unlock(&philo->philo_lock);

	pthread_mutex_lock(&philo->table->table_lock);
	philo->table->synchro_run_nbr++;
	pthread_mutex_unlock(&philo->table->table_lock);

	ft_write_state_change(LEFT_HAND, philo);
	while (!ft_no_race_argcheck(&philo->table->done, &philo->table->table_lock))
		usleep(50);
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
			if (pthread_create(&table->p[i].tid, NULL, ft_routine, &table->p[i]) != 0)
			{
				printf("ERROR: thread creation error!!!");
				table->p[i].tid = 0;
			}
			i++;
		}
	}
	//monitoring
	pthread_create(&table->table_monitor, NULL, ft_routine_monitor, table);
	
	//
	table->start_time = ft_take_time();

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
