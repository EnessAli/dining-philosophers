#include "philo.h"
#include <unistd.h>

int	check_dead_function(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->m_time);
	if (get_time() - philo->last_eat >= table->time_of_die)
	{
		pthread_mutex_unlock(&table->m_time);
		pthread_mutex_lock(&table->m_die);
		table->check_die = 1;
		table->die_time = get_time() - table->table_start_time;
		pthread_mutex_unlock(&table->m_die);
		return (ERROR);
	}
	pthread_mutex_unlock(&table->m_time);
	return (SUCCESS);
}

int	sushi2(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->m_fork[philo->right_fork]);
	pthread_mutex_lock(&table->m_die);
	if (table->check_die == 1)
		return (pthread_mutex_unlock(&table->m_die), ERROR);
	pthread_mutex_unlock(&table->m_die);
	print_at_all(table, "has taken a right chopStick.", philo->philo_id);
	pthread_mutex_lock(&table->m_die);
	if (table->check_die == 1)
		return (pthread_mutex_unlock(&table->m_die), ERROR);
	pthread_mutex_unlock(&table->m_die);
	print_at_all(table, "is eating.", philo->philo_id);
	baby_sleep(table->time_of_eat);
	pthread_mutex_lock(&table->m_time);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&table->m_time);
	philo->eat_count++;
	pthread_mutex_unlock(&table->m_fork[philo->left_fork]);
	pthread_mutex_unlock(&table->m_fork[philo->right_fork]);
	return (SUCCESS);
}

int	sushi(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->m_fork[philo->left_fork]);
	pthread_mutex_lock(&table->m_die);
	if (table->check_die == 1)
		return (pthread_mutex_unlock(&table->m_die), ERROR);
	pthread_mutex_unlock(&table->m_die);
	print_at_all(table, "has taken a left chopStick.", philo->philo_id);
	if (table->num_of_philo == 1)
	{
		pthread_mutex_unlock(&table->m_fork[philo->left_fork]);
		pthread_mutex_lock(&table->m_die);
		while (table->check_die != 1)
		{
			pthread_mutex_unlock(&table->m_die);
			usleep (100);
			pthread_mutex_lock(&table->m_die);
		}
		return (pthread_mutex_unlock(&table->m_die), ERROR);
	}
	return (sushi2(table, philo));
}

int	yummy(t_table *table, t_philo *philo)
{
	if (sushi(table, philo) != SUCCESS)
		return (ERROR);
	pthread_mutex_lock(&table->m_die);
	if (table->check_die == 1)
		return (pthread_mutex_unlock(&table->m_die), ERROR);
	pthread_mutex_unlock(&table->m_die);
	print_at_all(table, "is sleeping.", philo->philo_id);
	baby_sleep(table->time_of_sleep);
	pthread_mutex_lock(&table->m_die);
	if (table->check_die == 1)
		return (pthread_mutex_unlock(&table->m_die), ERROR);
	pthread_mutex_unlock(&table->m_die);
	print_at_all(table, "is thinking.", philo->philo_id);
	return (SUCCESS);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 != 1)
		baby_sleep(10);
	while (!yummy(philo->table, philo))
	{
		pthread_mutex_lock(&philo->table->m_with_eat);
		if (philo->eat_count == philo->table->eat_limit)
		{
			philo->table->check_eat_count++;
			pthread_mutex_unlock(&philo->table->m_with_eat);
			break ;
		}
		pthread_mutex_unlock(&philo->table->m_with_eat);
	}
	return (NULL);
}
