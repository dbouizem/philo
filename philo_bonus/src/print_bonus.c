/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:26:08 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/05 01:26:09 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		is_death;

	is_death = (status[0] == 'd');
	if (philo->data->stop && !is_death)
		return ;
	sem_wait(philo->data->print_sem);
	if (philo->data->stop && !is_death)
	{
		sem_post(philo->data->print_sem);
		return ;
	}
	timestamp = get_time_in_ms() - philo->data->start_time;
	if (!philo->data->stop || is_death)
		printf("%ld %d %s\n", timestamp, philo->id, status);
	sem_post(philo->data->print_sem);
}
