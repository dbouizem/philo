#include "../includes/philo_bonus.h"

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

	sem_wait(philo->data->print_sem);
	timestamp = get_time_in_ms() - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, status);
	sem_post(philo->data->print_sem);
}
