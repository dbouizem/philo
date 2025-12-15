#include "../includes/philo.h"

void	print_error(char *message)
{
	write(2, message, strlen(message));
	write(2, "\n", 1);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (0);
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		result = result * 10 + (str[i] - '0');
		if (result > 2147483647)
			return (-1);
		i++;
	}
	return ((int)result);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
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
		if (is_death_message)
			fflush(stdout);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}
