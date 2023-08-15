#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

struct s_philo;
typedef struct s_help
{
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				number_of_philosophers;
	int				eat_num;
	int				die;
	int				eat_check;
	unsigned long	sta_time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*write;
	struct s_philo	*philo;
}					t_help;

typedef struct s_philo
{
	int				left_fork;
	int				right_fork;
	int				id;
	int				eat_count;
	long long		time_die;
	pthread_mutex_t	*eat;
	t_help			*help;
	pthread_t		thread_id;
}					t_philo;

int					ft_strlen(char *str);
int					check_error(char **av);
int					ft_atoi(char *str);
void				ft_check_meals(t_help *help);
int					check(int *arr, int num_philo);
void				fill(int *arr, int number_of_philosophers);
int					ft_init_thread(t_help *help);
int					ft_check_errors(char **av);
int	ft_check_args(t_help *help);
int	ft_help_initp(t_help *help, char **av, int ac);
unsigned long	ft_time(void);
void	ft_time1(int wait_time);
int ft_write_error(char *s);
int	ft_init_help(t_help *help);

#endif
