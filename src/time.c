#include "../includes/philo.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	check_simulation_ended(t_data *data)
{
	int	ended;

	pthread_mutex_lock(&data->stop_mutex);
	ended = data->simulation_ended;
	pthread_mutex_unlock(&data->stop_mutex);
	return (ended);
}

void	set_simulation_ended(t_data *data, int value)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->simulation_ended = value;
	pthread_mutex_unlock(&data->stop_mutex);
}

void	ft_usleep(long duration_ms, t_data *data)
{
	long	start;
	long	elapsed;

	start = get_time_in_ms();
	while (1)
	{
		if (check_simulation_ended(data))
			break ;
		elapsed = get_time_in_ms() - start;
		if (elapsed >= duration_ms)
			break ;
		usleep(500);
	}
}
