#include "philo.h"

int	ft_check_errors(char **av)
{
	if (check_error(av) == 0)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	return (1);
}

int	ft_check_args(t_help *help)
{
	if (help->number_of_philosophers < 1)
		return (1);
	if (help->time_to_eat < 0
		|| help->time_to_sleep < 0 || help->time_to_die < 0)
		return (-1);
	return (0);
}

int	ft_help_initp(t_help *help, char **av, int ac)
{
	if (ft_check_args(help) == 1)
		return (-1);
	if (ac == 6)
	{
		help->eat_num = ft_atoi(av[5]);
		if (help->eat_num <= 0)
			return (-1);
	}
	else
		help->eat_num = -1;
	if (ft_init_help(help))
		return (-1);
	return (0);
}

unsigned long	ft_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_time1(int wait_time)
{
	unsigned long	cur;

	cur = ft_time();
	while (cur + wait_time > ft_time())
		usleep(100);
}
