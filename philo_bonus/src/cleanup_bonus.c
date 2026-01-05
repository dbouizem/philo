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

static void	close_semaphores(t_data *data)
{
	if (data->forks && data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->print_sem && data->print_sem != SEM_FAILED)
		sem_close(data->print_sem);
	if (data->stop_sem && data->stop_sem != SEM_FAILED)
		sem_close(data->stop_sem);
	if (data->seats_sem && data->seats_sem != SEM_FAILED)
		sem_close(data->seats_sem);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_SEATS);
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
			i++;
		}
		free(data->philos);
	}
	close_semaphores(data);
}
