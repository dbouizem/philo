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
	while (1)
	{
		sem_wait(philo->meal_sem);
		last_meal_time = philo->last_meal_time;
		sem_post(philo->meal_sem);
		if (get_time_in_ms() - last_meal_time > philo->data->time_to_die)
		{
			print_status(philo, "died");
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}
