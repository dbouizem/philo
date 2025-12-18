#include "../includes/philo.h"

static pthread_mutex_t	*get_first_fork(t_philo *philo)
{
	if (philo->left_fork < philo->right_fork)
		return (philo->left_fork);
	return (philo->right_fork);
}

static pthread_mutex_t	*get_second_fork(t_philo *philo)
{
	if (get_first_fork(philo) == philo->left_fork)
		return (philo->right_fork);
	return (philo->left_fork);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = get_first_fork(philo);
	second_fork = get_second_fork(philo);
	if (check_simulation_ended(philo->data))
		return (0);
	pthread_mutex_lock(first_fork);
	print_status(philo, "has taken a fork");
	if (check_simulation_ended(philo->data))
	{
		pthread_mutex_unlock(first_fork);
		return (0);
	}
	pthread_mutex_lock(second_fork);
	print_status(philo, "has taken a fork");
	if (check_simulation_ended(philo->data))
	{
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		return (0);
	}
	return (1);
}

void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}
