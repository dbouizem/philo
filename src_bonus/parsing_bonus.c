#include "../includes/philo_bonus.h"

static int	check_overflow(t_data *data)
{
	if (data->nb_philos == -1 || data->time_to_die == -1
		|| data->time_to_eat == -1 || data->time_to_sleep == -1)
	{
		print_error("Error: Value too large (max 2147483647)");
		return (1);
	}
	return (0);
}

static int	check_positive_values(t_data *data, int argc)
{
	if (data->nb_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		print_error("Error: All values must be strictly positive");
		return (1);
	}
	if (argc == 6 && data->nb_meals <= 0)
	{
		print_error("Error: number_of_times_each_philosopher_must_eat"
			" must be positive");
		return (1);
	}
	return (0);
}

static int	validate_numbers(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			print_error("Error: All arguments must be positive numbers");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	set_nb_meals(int argc, char **argv, t_data *data)
{
	if (argc == 6)
	{
		data->nb_meals = ft_atoi(argv[5]);
		if (data->nb_meals == -1)
		{
			print_error("Error: Value too large (max 2147483647)");
			return (1);
		}
	}
	else
		data->nb_meals = -1;
	return (0);
}

int	parse_arguments(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		print_error("Usage: ./philo_bonus number_of_philosophers time_to_die"
			" time_to_eat time_to_sleep"
			" [number_of_times_each_philosopher_must_eat]");
		return (1);
	}
	if (validate_numbers(argc, argv) != 0)
		return (1);
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (check_overflow(data) != 0)
		return (1);
	if (set_nb_meals(argc, argv, data) != 0)
		return (1);
	return (check_positive_values(data, argc));
}
