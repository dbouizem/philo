/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:26:57 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/15 01:40:40 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

# define SEM_FORKS "/philo_forks"
# define SEM_PRINT "/philo_print"
# define SEM_SEATS "/philo_seats"

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_meals;
	long			start_time;
	int				stop;
	int				exit_status;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*seats_sem;
	t_philo			*philos;
}	t_data;

typedef struct s_philo
{
	int			id;
	pid_t		pid;
	long		last_meal_time;
	int			meals_eaten;
	sem_t		*meal_sem;
	sem_t		*stop_sem;
	pthread_t	monitor_thread;
	pthread_t	stop_thread;
	int			monitor_started;
	int			stop_started;
	t_data		*data;
}	t_philo;

int		parse_arguments(int argc, char **argv, t_data *data);
void	print_error(char *message);
void	print_status(t_philo *philo, char *status);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		is_valid_number(char *str);
long	get_time_in_ms(void);
void	ft_usleep(t_data *data, long duration_ms);
int		init_data(t_data *data);
void	cleanup_data(t_data *data);
void	cleanup_child(t_data *data);
void	signal_stop(t_data *data);
int		create_processes(t_data *data);
void	philosopher_routine(t_philo *philo);
void	*monitor_routine(void *arg);
int		take_forks(t_philo *philo);
void	put_down_forks(t_philo *philo);
void	eat(t_philo *philo);
void	sleep_philo(t_philo *philo);
void	think(t_philo *philo);

#endif
