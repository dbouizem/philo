/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:25:49 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/05 01:27:57 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static int	init_semaphores(t_data *data)
{
	int	seats;

	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_STOP);
	sem_unlink(SEM_SEATS);
	data->forks = sem_open(SEM_FORKS, O_CREAT, 0644, data->nb_philos);
	if (data->forks == SEM_FAILED)
		return (print_error("Error: sem_open forks"), 1);
	data->print_sem = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		return (print_error("Error: sem_open print"), 1);
	data->stop_sem = sem_open(SEM_STOP, O_CREAT, 0644, 1);
	if (data->stop_sem == SEM_FAILED)
		return (print_error("Error: sem_open stop"), 1);
	seats = data->nb_philos - 1;
	if (seats < 1)
		seats = 1;
	data->seats_sem = sem_open(SEM_SEATS, O_CREAT, 0644, seats);
	if (data->seats_sem == SEM_FAILED)
		return (print_error("Error: sem_open seats"), 1);
	return (0);
}

static void	build_meal_sem_name(char *name, int id)
{
	const char	*prefix = "/philo_meal_";
	char		tmp[12];
	int			i;
	int			j;

	i = 0;
	while (prefix[i])
	{
		name[i] = prefix[i];
		i++;
	}
	if (id == 0)
		name[i++] = '0';
	j = 0;
	while (id > 0)
	{
		tmp[j++] = (id % 10) + '0';
		id /= 10;
	}
	while (j > 0)
		name[i++] = tmp[--j];
	name[i] = '\0';
}

static int	init_philo_entry(t_data *data, int i)
{
	char	name[32];

	data->philos[i].id = i + 1;
	data->philos[i].pid = 0;
	data->philos[i].meals_eaten = 0;
	data->philos[i].last_meal_time = data->start_time;
	data->philos[i].data = data;
	build_meal_sem_name(name, data->philos[i].id);
	sem_unlink(name);
	data->philos[i].meal_sem = sem_open(name, O_CREAT, 0644, 1);
	if (data->philos[i].meal_sem == SEM_FAILED)
		return (print_error("Error: sem_open meal"), 1);
	sem_unlink(name);
	return (0);
}

static int	init_philos(t_data *data)
{
	int		i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		return (print_error("Error: malloc"), 1);
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].meal_sem = SEM_FAILED;
		if (init_philo_entry(data, i) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_data(t_data *data)
{
	data->start_time = get_time_in_ms();
	if (init_semaphores(data) != 0)
		return (1);
	if (init_philos(data) != 0)
		return (1);
	return (0);
}
