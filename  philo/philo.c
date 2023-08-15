#include "philo.h"

int	ft_init_help(t_help *help)
{
	int	i;

	i = 0;
	help->philo = malloc(sizeof(t_philo) * help->number_of_philosophers);
	while (i < help->number_of_philosophers)
	{
		help->philo[i].help = help;
		i++;
	}
	i = 0;
	if (!help->philo)
		return (-1);
	while (i < help->number_of_philosophers)
	{
		help->philo[i].eat = malloc(sizeof(pthread_mutex_t));
		help->philo[i].right_fork = (i + 1) % help->number_of_philosophers;
		help->philo[i].left_fork = i;
		help->philo[i].help = help;
		help->philo[i].time_die = 0;
		help->philo[i].eat_count = 0;
		help->philo[i].id = i + 1;
		i++;
	}
	return (0);
}

int	ft_init_philo(t_help *help, char **av, int ac)
{
	help->die = 0;
	help->eat_check = 0;
	help->sta_time = 0;
	help->time_to_eat = ft_atoi(av[3]);
	help->time_to_sleep = ft_atoi(av[4]);
	help->time_to_die = ft_atoi(av[2]);
	help->number_of_philosophers = ft_atoi(av[1]);
	ft_help_initp(help, av, ac);
	return (0);
}

void ft_help_thred(t_philo *philo)
{
	pthread_mutex_lock(philo->eat);
	if (philo->help->eat_num > 0)
		philo->eat_count++;
	pthread_mutex_unlock(philo->eat);
	pthread_mutex_lock(philo->help->write);
	printf("%lu %d  is sleeping! \n", 
		(ft_time() - philo->help->sta_time), philo->id);
	pthread_mutex_unlock(philo->help->write);
	ft_time1(philo->help->time_to_sleep);
	pthread_mutex_lock(philo->help->write);
	printf("%lu %d  is thinking! \n",
		(ft_time() - philo->help->sta_time), philo->id);
	pthread_mutex_unlock(philo->help->write);
}

void ft_help_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->eat);
	philo->time_die = ft_time();
	pthread_mutex_unlock(philo->eat);
	pthread_mutex_lock(philo->help->write);
	printf("%lu %d is eating!\n", (ft_time() - philo->help->sta_time), philo->id);
	pthread_mutex_unlock(philo->help->write);
	ft_time1(philo->help->time_to_eat);
}

void *ft_thread(void *philox)
{
	while (1)
	{
		t_philo *philo = philox;
		pthread_mutex_lock(&philo->help->fork[philo->left_fork]);
		pthread_mutex_lock(philo->help->write);
		printf("%lu %d  has taken fork 1!\n", 
			(ft_time() - philo->help->sta_time), philo->id);
		pthread_mutex_unlock(philo->help->write);
		pthread_mutex_lock(&philo->help->fork[philo->right_fork]);
		pthread_mutex_lock(philo->help->write);
		printf("%lu %d  has taken fork 2!\n", 
			(ft_time() - philo->help->sta_time), philo->id);
		pthread_mutex_unlock(philo->help->write);
		ft_help_eating(philo);
		pthread_mutex_unlock(&philo->help->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->help->fork[philo->right_fork]);
		ft_help_thred(philo);
	}
	return (NULL);
}
void ft_he_philo(t_help *help)
{
	int	i;

	i = 0;
	help->sta_time = ft_time();
	while (i < help->number_of_philosophers)
	{
		help->philo[i].time_die = ft_time();
		pthread_create(&(help->philo[i].thread_id), NULL, ft_thread, &help->philo[i]);
		usleep(40);
		i++;
	}
}

int ft_help_end(t_help *help, int *arr, int *j, int*i)
{
	arr[(*i)] = 1;
	if (check(arr, help->number_of_philosophers) == 0)
	{
		pthread_mutex_lock(help->write);
		while ((*j) < help->number_of_philosophers)
		{
			pthread_detach(help->philo[(*j)].thread_id);
			(*j)++;
		}
		printf("finish\n");
		return (0);
	}
	return(1);
}
int ft_help_dead(t_help *help, int *i)
{
	pthread_mutex_lock(help->write);
	printf("%llu %d is dead\n", 
		ft_time() - help->philo[(*i)].time_die, (*i) + 1);
	(*i) = 0;
	while((*i) < help->number_of_philosophers)
	{
		pthread_detach(help->philo[(*i)].thread_id);
		(*i)++;
	}
	sleep(1);
	return (0);
}

int ft_philo(t_help *help)
{
	int i;
	int arr[255];
	int j;

	j = 0;
	i = 0;
	ft_he_philo(help);
	fill(arr, help->number_of_philosophers);
	i = 0;
	while (i < help->number_of_philosophers)
	{
		pthread_mutex_lock(help->philo[i].eat);
		if (help->eat_num > 0 && help->philo[i].eat_count >= help->eat_num)
			ft_help_end(help, arr, &j, &i);
		if (ft_time() - help->philo[i].time_die > help->time_to_die)
			ft_help_dead(help, &i);
		i++;
		if (i == help->number_of_philosophers)
			i = 0;
		pthread_mutex_unlock(help->philo[i].eat);
	}
	return (0);
}

int main(int ac, char *av[])
{
	t_help help;

	if (ac != 5 && ac != 6)
	{
		printf("sadfdsa");
		return (ft_write_error("ERROR args"));
	}
	// if (!check_error(av))
	// 	return (ft_write_error("ERROR args"));
	if (ft_init_philo(&help, av, ac))
	{
		return (ft_write_error("ERROR init param"));
	}
	if (ft_init_thread(&help))
	{
		return (ft_write_error("ERROR init param"));
	}
	if (ft_philo(&help))
	{
		return (ft_write_error("ERROR philo"));
	}
	return (0);
}
