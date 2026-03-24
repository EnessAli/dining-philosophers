#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

int	waiting_threads(t_table *table, int i)
{
	while (++i < table->num_of_philo)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				&philo_life, &table->philo[i]))
			return (ERROR);
	}
	while (1)
	{
		i = -1;
		while (++i < table->num_of_philo)
		{
			pthread_mutex_lock(&table->m_with_eat);
			if (check_dead_function(table, &table->philo[i])
				|| table->check_eat_count == table->num_of_philo)
			{
				pthread_mutex_unlock(&table->m_with_eat);
				table->die_id = i + 1;
				break ;
			}
			pthread_mutex_unlock(&table->m_with_eat);
		}
		if (i != table->num_of_philo)
			break ;
	}
	return (SUCCESS);
}

int	start_simulation(t_table *table, int i)
{
	if (waiting_threads(table, -1))
		return (ERROR);
	while (++i < table->num_of_philo)
	{
		if (pthread_join(table->philo[i].thread, NULL))
			return (ERROR);
	}
	if (table->check_die)
		printf("%llu %d is died\n", table->die_time, table->die_id);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (argument_control(ac, av))
		return (ft_putstr_fd(CHECK_ARGS, 2), ERROR);
	if (creating_table(&table, av) != SUCCESS)
		return (ft_putstr_fd(CREATING_TABLE_ERROR, 2),
			destroy_mutex(&table, table.num), ERROR);
	table.philo = (t_philo *)malloc(sizeof(t_philo) * table.num_of_philo);
	if (!table.philo)
		return (ft_putstr_fd(M_ERROR, 2),
			destroy_mutex(&table, table.num_of_philo + 5), ERROR);
	if (table.num_of_philo == 0)
		return (destroy_mutex(&table, table.num_of_philo + 5), ERROR);
	init_philo(&table);
	if (start_simulation(&table, -1))
		return (ft_putstr_fd(START_SIMULATION_ERROR, 2),
			destroy_mutex(&table, table.num_of_philo + 5), ERROR);
	return (destroy_mutex(&table, table.num_of_philo + 5), SUCCESS);
}
