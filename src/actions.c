#include "../includes/philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo->data);
}

void	sleep_philo(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	think(t_philo *philo)
{
	long	think_time;
	long	slack_time;

	print_status(philo, "is thinking");
	if (philo->data->nb_philos % 2 != 0)
	{
		slack_time = philo->data->time_to_die
			- (philo->data->time_to_eat + philo->data->time_to_sleep);
		if (slack_time <= 0)
			return ;
		think_time = slack_time / 2;
		ft_usleep(think_time, philo->data);
	}
}
