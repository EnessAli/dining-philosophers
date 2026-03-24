#include "philo.h"
#include <stdio.h>

void	print_at_all(t_table *table, char *str, int number)
{
	pthread_mutex_lock(&table->m_time);
	printf("%llu %d %s\n", get_time() - table->table_start_time, number, str);
	pthread_mutex_unlock(&table->m_time);
}

int	mutex_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
		if (pthread_mutex_init(&table->m_fork[i], NULL) != SUCCESS)
			return (table->num = i, ERROR);
	if (pthread_mutex_init(&table->m_print, NULL) != SUCCESS)
		return (printf(MUTEX_INIT_ERROR),
			table->num = table->num_of_philo, ERROR);
	if (pthread_mutex_init(&table->m_die, NULL) != SUCCESS)
		return (printf(MUTEX_INIT_ERROR),
			table->num = table->num_of_philo + 1, ERROR);
	if (pthread_mutex_init(&table->m_time, NULL) != SUCCESS)
		return (printf(MUTEX_INIT_ERROR),
			table->num = table->num_of_philo + 2, ERROR);
	if (pthread_mutex_init(&table->m_eat, NULL) != SUCCESS)
		return (printf(MUTEX_INIT_ERROR),
			table->num = table->num_of_philo + 3, ERROR);
	if (pthread_mutex_init(&table->m_with_eat, NULL) != SUCCESS)
		return (printf(MUTEX_INIT_ERROR),
			table->num = table->num_of_philo + 4, ERROR);
	return (SUCCESS);
}

void	init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo)
	{
		table->philo[i].philo_id = i + 1;
		table->philo[i].eat_count = 0;
		table->philo[i].left_fork = i;
		table->philo[i].right_fork = (i + 1) % table->num_of_philo;
		table->philo[i].last_eat = table->table_start_time;
		table->philo[i].table = table;
	}
}

int	destroy_mutex(t_table *table, int num)
{
	int	i;

	i = -1;
	while (++i < table->num_of_philo && i < num)
		pthread_mutex_destroy(&table->m_fork[i]);
	if (i++ < num)
		pthread_mutex_destroy(&table->m_print);
	if (i++ < num)
		pthread_mutex_destroy(&table->m_die);
	if (i++ < num)
		pthread_mutex_destroy(&table->m_time);
	if (i++ < num)
		pthread_mutex_destroy(&table->m_eat);
	if (i++ < num)
		pthread_mutex_destroy(&table->m_with_eat);
	return (ft_no_malloc(table));
}
