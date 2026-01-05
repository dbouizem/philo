/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:26:22 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/05 01:26:23 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long duration_ms)
{
	long	start;
	long	elapsed;

	start = get_time_in_ms();
	while (1)
	{
		elapsed = get_time_in_ms() - start;
		if (elapsed >= duration_ms)
			break ;
		usleep(500);
	}
}
