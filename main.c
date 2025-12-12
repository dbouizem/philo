#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	// Parser les arguments
	if (parse_arguments(argc, argv, &data) != 0)
		return (1);

	// Debug
	printf("=== Parsing réussi ===\n");
	printf("Nombre de philosophes: %d\n", data.nb_philos);
	printf("Time to die: %ld ms\n", data.time_to_die);
	printf("Time to eat: %ld ms\n", data.time_to_eat);
	printf("Time to sleep: %ld ms\n", data.time_to_sleep);
	if (data.nb_meals != -1)
		printf("Number of meals: %d\n", data.nb_meals);
	else
		printf("Number of meals: unlimited\n");

	// TODO: Initialisation de la simulation (étape 4)
	// TODO: Création des threads (étape 5)
	// TODO: Nettoyage (étape 12)
	return (0);
}
