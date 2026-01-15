/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:26:14 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/05 01:26:15 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	*stop_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (sem_wait(philo->stop_sem) == 0)
		philo->data->stop = 1;
	return (NULL);
}

static void	start_monitor(t_philo *philo)
{
	philo->last_meal_time = get_time_in_ms();
	if (pthread_create(&philo->monitor_thread, NULL,
			monitor_routine, philo) != 0)
	{
		print_error("Error: Failed to create monitor thread");
		philo->data->exit_status = 1;
		philo->data->stop = 1;
		return ;
	}
	philo->monitor_started = 1;
}

static void	start_stop_watcher(t_philo *philo)
{
	if (pthread_create(&philo->stop_thread, NULL,
			stop_routine, philo) != 0)
	{
		print_error("Error: Failed to create stop thread");
		philo->data->exit_status = 1;
		philo->data->stop = 1;
		return ;
	}
	philo->stop_started = 1;
}

static void	child_exit(t_philo *philo, int status)
{
	philo->data->stop = 1;
	if (philo->stop_started && philo->stop_sem
		&& philo->stop_sem != SEM_FAILED)
		sem_post(philo->stop_sem);
	if (philo->monitor_started)
		pthread_join(philo->monitor_thread, NULL);
	if (philo->stop_started)
		pthread_join(philo->stop_thread, NULL);
	cleanup_child(philo->data);
	exit(status);
}

void	philosopher_routine(t_philo *philo)
{
	start_stop_watcher(philo);
	start_monitor(philo);
	if (philo->data->stop)
		child_exit(philo, philo->data->exit_status);
	if (philo->id % 2 == 0)
		usleep(500);
	while (!philo->data->stop)
	{
		if (take_forks(philo))
			break ;
		eat(philo);
		put_down_forks(philo);
		if (philo->data->nb_meals != -1
			&& philo->meals_eaten >= philo->data->nb_meals)
		{
			philo->data->exit_status = 0;
			philo->data->stop = 1;
			break ;
		}
		sleep_philo(philo);
		think(philo);
	}
	child_exit(philo, philo->data->exit_status);
}
