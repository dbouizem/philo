#include "../includes/philo.h"

static int	init_mutexes(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->stop_mutex, NULL) != 0)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

static int	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philos];
		if (pthread_mutex_init(&data->philos[i].meal_mutex, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_simulation(t_data *data)
{
	data->simulation_ended = 0;
	if (init_mutexes(data) != 0)
		return (print_error("Error: Failed to initialize mutexes"), 1);
	data->start_time = get_time_in_ms();
	if (init_philosophers(data) != 0)
		return (print_error("Error: Failed to initialize philosophers"), 1);
	return (0);
}

void	cleanup_simulation(t_data *data)
{
	int	i;

	if (data->philos)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_destroy(&data->philos[i].meal_mutex);
			i++;
		}
		free(data->philos);
	}
	if (data->forks)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
}
