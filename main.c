#include "includes/philo.h"

static void	wait_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (parse_arguments(argc, argv, &data) != 0)
		return (1);
	if (init_simulation(&data) != 0)
		return (1);
	if (create_philosophers(&data) != 0)
		return (cleanup_simulation(&data), 1);
	if (create_monitor(&data) != 0)
	{
		set_simulation_ended(&data, 1);
		wait_philosophers(&data);
		cleanup_simulation(&data);
		return (1);
	}
	wait_philosophers(&data);
	if (join_monitor(&data) != 0)
		return (cleanup_simulation(&data), 1);
	cleanup_simulation(&data);
	return (0);
}
