#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

# define SEM_FORKS "/philo_forks"
# define SEM_PRINT "/philo_print"

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int		nb_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		nb_meals;
	long	start_time;
	sem_t	*forks;
	sem_t	*print_sem;
	t_philo	*philos;
}	t_data;

typedef struct s_philo
{
	int			id;
	pid_t		pid;
	long		last_meal_time;
	int			meals_eaten;
	pthread_t	monitor_thread;
	t_data		*data;
}	t_philo;

int		parse_arguments(int argc, char **argv, t_data *data);
void	print_error(char *message);
void	print_status(t_philo *philo, char *status);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		is_valid_number(char *str);
long	get_time_in_ms(void);
void	ft_usleep(long duration_ms);
int		init_data(t_data *data);
void	cleanup_data(t_data *data);
int		create_processes(t_data *data);
void	philosopher_routine(t_philo *philo);
void	*monitor_routine(void *arg);
void	take_forks(t_philo *philo);
void	put_down_forks(t_philo *philo);
void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think(t_philo *philo);

#endif
