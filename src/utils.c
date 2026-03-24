#include "philo.h"
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

u_int64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	baby_sleep(u_int64_t time)
{
	u_int64_t	start;

	start = get_time() + time;
	while (get_time() < start)
		usleep(200);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_no_malloc(t_table *table)
{
	free(table->philo);
	free(table->m_fork);
	return (SUCCESS);
}
