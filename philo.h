#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	// Paramètres du programme
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				nb_meals;			// -1 si non spécifié

	// Temps
	long			start_time;			// Timestamp de démarrage

	// État de la simulation
	int				simulation_ended;	// Flag d'arrêt (0 ou 1)
	int				all_ate_enough;		// Tous ont mangé nb_meals

	// Mutex globaux
	pthread_mutex_t	print_mutex;		// Protège les printf
	pthread_mutex_t	stop_mutex;			// Protège simulation_ended
	pthread_mutex_t	*forks;				// Tableau de mutex (fourchettes)

	// Philosophes
	t_philo			*philos;			// Tableau des philosophes
}	t_data;

typedef struct s_philo
{
	int				id;					// Numéro du philosophe (1 à N)
	pthread_t		thread;				// Son thread

	// État du philosophe
	long			last_meal_time;		// Timestamp du dernier repas
	int				meals_eaten;		// Nombre de repas mangés

	// Synchronisation
	pthread_mutex_t	meal_mutex;			// Protège last_meal_time et meals_eaten

	// Fourchettes
	pthread_mutex_t	*left_fork;			// Pointeur vers mutex gauche
	pthread_mutex_t	*right_fork;		// Pointeur vers mutex droite

	// Données globales
	t_data			*data;				// Pointeur vers structure globale
}	t_philo;

int		parse_arguments(int argc, char **argv, t_data *data);

void	print_error(char *message);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		is_valid_number(char *str);


#endif
