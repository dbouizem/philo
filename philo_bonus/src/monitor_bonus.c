/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:25:58 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/05 01:25:59 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	long	last_meal_time;

	philo = (t_philo *)arg;
	while (!philo->data->stop)
	{
		if (sem_wait(philo->meal_sem) != 0)
			continue ;
		last_meal_time = philo->last_meal_time;
		sem_post(philo->meal_sem);
		if (get_time_in_ms() - last_meal_time > philo->data->time_to_die)
		{
			philo->data->exit_status = 1;
			philo->data->stop = 1;
			print_status(philo, "died");
			signal_stop(philo->data);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
