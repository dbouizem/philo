#include "../includes/philo.h"

static void	*one_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philos == 1)
		return (one_philo_routine(philo));
	if (philo->id % 2 == 0)
		ft_usleep(1, philo->data);
	while (!check_simulation_ended(philo->data))
	{
		think(philo);
		take_forks(philo);
		eat(philo);
		put_down_forks(philo);
		sleep_philo(philo);
	}
	return (NULL);
}

int	create_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]) != 0)
		{
			print_error("Error: Failed to create philosopher thread");
			return (1);
		}
		i++;
	}
	return (0);
}
