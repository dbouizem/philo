#include "../includes/philo_bonus.h"

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (get_time_in_ms() - philo->last_meal_time > philo->data->time_to_die)
		{
			print_status(philo, "died");
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}
