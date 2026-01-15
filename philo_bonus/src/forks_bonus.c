/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:25:33 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/05 01:25:34 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	release_forks(t_philo *philo, int forks)
{
	if (forks >= 1)
		sem_post(philo->data->forks);
	if (forks >= 2)
		sem_post(philo->data->forks);
	sem_post(philo->data->seats_sem);
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (philo->data->stop)
		return (1);
	if (sem_wait(philo->data->seats_sem) != 0)
		return (1);
	if (philo->data->stop)
		return (release_forks(philo, 0));
	if (sem_wait(philo->data->forks) != 0)
		return (release_forks(philo, 0));
	if (philo->data->stop)
		return (release_forks(philo, 1));
	print_status(philo, "has taken a fork");
	if (sem_wait(philo->data->forks) != 0)
		return (release_forks(philo, 1));
	if (philo->data->stop)
		return (release_forks(philo, 2));
	print_status(philo, "has taken a fork");
	return (0);
}

void	put_down_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	sem_post(philo->data->seats_sem);
}
