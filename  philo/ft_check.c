#include "philo.h"

void	ft_check_meals(t_help *help)
{
	int	i;

	i = 0;
	while (help->eat_num != 0
		&& i < help->number_of_philosophers
		&& help->philo[i].eat_count > help->eat_num)
		i++;
	if (i == help->number_of_philosophers)
		help->eat_check = 1;
}

int	check(int *arr, int num_philo)
{
	int	i;

	i = 0;
	while (arr[i] == 1)
		i++;
	if (i == num_philo)
		return (0);
	return (1);
}

void	fill(int *arr, int number_of_philosophers)
{
	int	j;

	j = 0;
	while (j < number_of_philosophers)
	{
		arr[j] = 0;
		j++;
	}
}

int	ft_init_thread(t_help *help)
{
	int	i;

	i = 0;
	help->write = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init((help->write), NULL);
	help->fork = malloc(sizeof(pthread_mutex_t) * help->number_of_philosophers);
	if (!(help->fork))
		return (-1);
	while (i < help->number_of_philosophers)
	{
		pthread_mutex_init(help->fork + i, NULL);
		i++;
	}
	return (0);
}
