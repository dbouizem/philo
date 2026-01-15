/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 01:25:54 by dbouizem          #+#    #+#             */
/*   Updated: 2026/01/05 01:25:55 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	wait_children(t_data *data)
{
	int		i;
	int		status;
	pid_t	pid;
	int		stopped;

	i = 0;
	stopped = 0;
	while (i < data->nb_philos)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (!stopped && ((WIFEXITED(status) && WEXITSTATUS(status) != 0)
				|| WIFSIGNALED(status)))
		{
			signal_stop(data);
			stopped = 1;
		}
		i++;
	}
}

int	create_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid < 0)
			return (print_error("Error: fork"), 1);
		if (data->philos[i].pid == 0)
			philosopher_routine(&data->philos[i]);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_arguments(argc, argv, &data) != 0)
		return (1);
	if (init_data(&data) != 0)
		return (1);
	if (create_processes(&data) != 0)
	{
		signal_stop(&data);
		cleanup_data(&data);
		return (1);
	}
	wait_children(&data);
	cleanup_data(&data);
	return (0);
}
