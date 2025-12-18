#include "../includes/philo.h"

static size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	print_error(char *message)
{
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
}

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;
	int		is_death_message;

	is_death_message = (status[0] == 'd');
	pthread_mutex_lock(&philo->data->print_mutex);
	if (is_death_message || !check_simulation_ended(philo->data))
	{
		timestamp = get_time_in_ms() - philo->data->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}
