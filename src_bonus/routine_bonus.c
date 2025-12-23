#include "../includes/philo_bonus.h"

static void	start_monitor(t_philo *philo)
{
	if (pthread_create(&philo->monitor_thread, NULL,
			monitor_routine, philo) != 0)
	{
		print_error("Error: Failed to create monitor thread");
		exit(1);
	}
	pthread_detach(philo->monitor_thread);
}

void	philosopher_routine(t_philo *philo)
{
	philo->last_meal_time = get_time_in_ms();
	start_monitor(philo);
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		take_forks(philo);
		eat(philo);
		put_down_forks(philo);
		if (philo->data->nb_meals != -1
			&& philo->meals_eaten >= philo->data->nb_meals)
			exit(0);
		sleep_philo(philo);
		think(philo);
	}
}
