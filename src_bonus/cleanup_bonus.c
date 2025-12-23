#include "../includes/philo_bonus.h"

static void	close_semaphores(t_data *data)
{
	if (data->forks && data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->print_sem && data->print_sem != SEM_FAILED)
		sem_close(data->print_sem);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
}

void	cleanup_data(t_data *data)
{
	if (data->philos)
		free(data->philos);
	close_semaphores(data);
}
