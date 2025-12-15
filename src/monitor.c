#include "../includes/philo.h"

static int	check_all_ate_enough(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->nb_meals == -1)
		return (0);
	i = 0;
	all_ate = 1;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].meals_eaten < data->nb_meals)
			all_ate = 0;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		if (!all_ate)
			break ;
		i++;
	}
	return (all_ate);
}

static int	check_philo_death(t_data *data)
{
	int		i;
	long	current_time;
	long	time_since_meal;

	current_time = get_time_in_ms();
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		time_since_meal = current_time - data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		if (time_since_meal > data->time_to_die)
			return (data->philos[i].id);
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		dead_philo_id;

	data = (t_data *)arg;
	ft_usleep(10, data);
	while (!check_simulation_ended(data))
	{
		dead_philo_id = check_philo_death(data);
		if (dead_philo_id > 0)
		{
			set_simulation_ended(data, 1);
			print_status(&data->philos[dead_philo_id - 1], "died");
			break ;
		}
		if (check_all_ate_enough(data))
		{
			set_simulation_ended(data, 1);
			break ;
		}
		usleep(1000);
	}
	return (NULL);
}

int	create_monitor(t_data *data)
{
	if (pthread_create(&data->monitor_thread, NULL,
			monitor_routine, data) != 0)
	{
		print_error("Error: Failed to create monitor thread");
		return (1);
	}
	return (0);
}

int	join_monitor(t_data *data)
{
	if (pthread_join(data->monitor_thread, NULL) != 0)
	{
		print_error("Error: Failed to join monitor thread");
		return (1);
	}
	return (0);
}
