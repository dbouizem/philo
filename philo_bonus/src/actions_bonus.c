/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:25:33 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/05 01:25:34 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->meal_sem);
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	sem_post(philo->meal_sem);
	print_status(philo, "is eating");
	ft_usleep(philo->data, philo->data->time_to_eat);
}

void	sleep_philo(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data, philo->data->time_to_sleep);
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
	ft_usleep(philo->data, think_time);
}
