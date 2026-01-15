/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:25:42 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/05 01:25:43 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	close_semaphores(t_data *data, int unlink_names)
{
	if (data->forks && data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->print_sem && data->print_sem != SEM_FAILED)
		sem_close(data->print_sem);
	if (data->seats_sem && data->seats_sem != SEM_FAILED)
		sem_close(data->seats_sem);
	if (unlink_names)
	{
		sem_unlink(SEM_FORKS);
		sem_unlink(SEM_PRINT);
		sem_unlink(SEM_SEATS);
	}
}

void	signal_stop(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (data->philos[i].stop_sem
			&& data->philos[i].stop_sem != SEM_FAILED)
			sem_post(data->philos[i].stop_sem);
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		if (data->seats_sem && data->seats_sem != SEM_FAILED)
			sem_post(data->seats_sem);
		if (data->forks && data->forks != SEM_FAILED)
		{
			sem_post(data->forks);
			sem_post(data->forks);
		}
		i++;
	}
}

void	cleanup_data(t_data *data)
{
	int	i;

	if (data->philos)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			if (data->philos[i].meal_sem
				&& data->philos[i].meal_sem != SEM_FAILED)
				sem_close(data->philos[i].meal_sem);
			if (data->philos[i].stop_sem
				&& data->philos[i].stop_sem != SEM_FAILED)
				sem_close(data->philos[i].stop_sem);
			i++;
		}
		free(data->philos);
	}
	close_semaphores(data, 1);
}

void	cleanup_child(t_data *data)
{
	int	i;

	if (data->philos)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			if (data->philos[i].meal_sem
				&& data->philos[i].meal_sem != SEM_FAILED)
				sem_close(data->philos[i].meal_sem);
			if (data->philos[i].stop_sem
				&& data->philos[i].stop_sem != SEM_FAILED)
				sem_close(data->philos[i].stop_sem);
			i++;
		}
		free(data->philos);
	}
	close_semaphores(data, 0);
}
