#include "philo.h"

int	ft_atoi(char *str)
{
	int				i;
	int				si;
	unsigned long	res;

	si = 1;
	res = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			si *= -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + str[i] - '0';
		if (res > 9223372036854775807 && si == 1)
			return (-1);
		else if (res > 9223372036854775807 && si == -1)
			return (0);
		i++;
	}
	return (si * res);
}

int	ft_isdigit(int arg)
{
	if ((arg >= '0' && arg <= '9'))
	{
		return (1);
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int ft_write_error(char *s)
{
	printf("%s\n", s);
	return (-1);
}

int check_error(char **av)
{
	int i;
	int j;

	i = 0;
	while (av[i])
	{
		j = 0;
		if (av[i][j] == '-')
			return (0);
		j++;
		if (av[i][j] == '\0')
			return (0);
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]))
			{
				printf("aaaa");
				return (0);
			}
			j++;
		}
		if (ft_strlen(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
