#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_meals;
	long			start_time;
	int				simulation_ended;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	*forks;
	pthread_t		monitor_thread;
	t_philo			*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			last_meal_time;
	int				meals_eaten;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

int		parse_arguments(int argc, char **argv, t_data *data);

void	print_error(char *message);
void	print_status(t_philo *philo, char *status);

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		is_valid_number(char *str);

long	get_time_in_ms(void);
int		check_simulation_ended(t_data *data);
void	set_simulation_ended(t_data *data, int value);
void	ft_usleep(long duration_ms, t_data *data);

int		init_simulation(t_data *data);
void	cleanup_simulation(t_data *data);

int		take_forks(t_philo *philo);
void	put_down_forks(t_philo *philo);
void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think(t_philo *philo);

void	*philosopher_routine(void *arg);
int		create_philosophers(t_data *data);

void	*monitor_routine(void *arg);
int		create_monitor(t_data *data);
int		join_monitor(t_data *data);

#endif
