#include "../includes/philo_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_status(philo, "has taken a fork");
}

void	put_down_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	eat(t_philo *philo)
{
	philo->last_meal_time = get_time_in_ms();
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	philo->meals_eaten++;
}

void	sleep_philo(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	long	think_time;
	long	slack;

	print_status(philo, "is thinking");
	if (philo->data->nb_philos % 2 == 0)
		return ;
	slack = philo->data->time_to_die
		- (philo->data->time_to_eat + philo->data->time_to_sleep);
	if (slack <= 0)
		return ;
	think_time = slack / 2;
	ft_usleep(think_time);
}
