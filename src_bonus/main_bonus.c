#include "../includes/philo_bonus.h"

static void	kill_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (data->philos[i].pid > 0)
			kill(data->philos[i].pid, SIGKILL);
		i++;
	}
}

static void	wait_children(t_data *data)
{
	int		i;
	int		status;
	pid_t	pid;

	i = 0;
	while (i < data->nb_philos)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			kill_all(data);
			break ;
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
		kill_all(&data);
		cleanup_data(&data);
		return (1);
	}
	wait_children(&data);
	cleanup_data(&data);
	return (0);
}
