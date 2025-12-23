#include "../includes/philo_bonus.h"

static int	init_semaphores(t_data *data)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	data->forks = sem_open(SEM_FORKS, O_CREAT, 0644, data->nb_philos);
	if (data->forks == SEM_FAILED)
		return (print_error("Error: sem_open forks"), 1);
	data->print_sem = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		return (print_error("Error: sem_open print"), 1);
	return (0);
}

static int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->philos)
		return (print_error("Error: malloc"), 1);
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].pid = 0;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].data = data;
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
