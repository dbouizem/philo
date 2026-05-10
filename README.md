# Philosophers

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![42](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)
[![POSIX Threads](https://img.shields.io/badge/POSIX-Threads-1f6feb?style=for-the-badge)](https://en.wikipedia.org/wiki/Pthreads)
[![Synchronization](https://img.shields.io/badge/Synchronization-Mutexes%20%26%20Semaphores-8a2be2?style=for-the-badge)](https://en.wikipedia.org/wiki/Semaphore_(programming))
[![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=for-the-badge)](https://github.com/42School/norminette)
![Grade](https://img.shields.io/badge/Grade-125%2F100-brightgreen?style=for-the-badge)

*"I think, therefore I am... hungry"*

Implémentation en C du problème des philosophes dîneurs — deux versions : threads + mutex (mandatory), processus + sémaphores (bonus).

---

## Table des matières

1. [Description du projet](#description-du-projet)
2. [Structure du dépôt](#structure-du-dépôt)
3. [Partie obligatoire — threads + mutex](#partie-obligatoire--threads--mutex)
4. [Partie bonus — processus + sémaphores](#partie-bonus--processus--sémaphores)
5. [Questions d'évaluation](#questions-dévaluation)
6. [Notions à apprendre](#notions-à-apprendre)
7. [Commandes utiles](#commandes-utiles)
8. [Problèmes courants](#problèmes-courants)
9. [Ressources](#ressources)

---

## Description du projet

N philosophes sont assis autour d'une table ronde. N fourchettes les séparent — une entre chaque paire. Un philosophe a besoin des **deux** fourchettes adjacentes pour manger.

![Table des philosophes](https://github.com/user-attachments/assets/14b1fdbb-36e8-46a4-91c0-a5d3e82b86df)

### Cycle de vie

Un philosophe alterne entre trois états :

| État | Condition |
|------|-----------|
| Penser | état par défaut |
| Manger | nécessite 2 fourchettes (gauche + droite) |
| Dormir | après avoir mangé |

### Conditions d'arrêt

- Un philosophe n'a pas mangé depuis `time_to_die` millisecondes → mort
- Tous ont mangé `nb_meals` fois → objectif atteint (optionnel)

### Défis à résoudre

| Problème | Description |
|----------|-------------|
| Deadlock | Tous prennent 1 fourchette et attendent la 2e indéfiniment |
| Race condition | Accès concurrent aux ressources partagées |
| Starvation | Un philosophe n'arrive jamais à obtenir 2 fourchettes |
| Data race | Lectures/écritures simultanées sur les mêmes données |

### Deux implémentations

| Aspect | Mandatory (philo) | Bonus (philo_bonus) |
|--------|-------------------|---------------------|
| Unité d'exécution | Threads | Processus |
| Mémoire | Partagée | Isolée |
| Synchronisation | Mutex | Sémaphores nommés |
| Fourchettes | `pthread_mutex_t forks[]` | `sem_t *` comptage |
| Anti-deadlock | Lock-ordering par adresse | `seats_sem = N−1` |
| Monitor | 1 thread global | 1 thread par processus |

---

## Structure du dépôt

```
.
├── philo/
│   ├── includes/
│   │   └── philo.h
│   └── srcs/
│       ├── main.c         # orchestration
│       ├── init.c         # allocation + init mutex
│       ├── routine.c      # routine des philosophes
│       ├── forks.c        # prise et libération des fourchettes
│       ├── monitor.c      # détection mort + objectif
│       ├── print.c        # affichage synchronisé
│       └── time.c         # horloge + ft_usleep précis
│
└── philo_bonus/
    ├── includes/
    │   └── philo_bonus.h
    └── srcs/
        ├── main_bonus.c      # fork() + waitpid()
        ├── init_bonus.c      # sémaphores globaux
        ├── routine_bonus.c   # routine d'un philosophe
        ├── monitor_bonus.c   # détection mort par processus
        ├── forks_bonus.c     # gestion des fourchettes
        ├── cleanup_bonus.c   # signal_stop() + cleanup
        ├── print_bonus.c     # affichage protégé
        ├── time_bonus.c      # gestion du temps
        ├── parsing_bonus.c   # validation des arguments
        └── utils_bonus.c     # utilitaires
```

---

## Partie obligatoire — threads + mutex

Un thread par philosophe + un thread monitor. Les fourchettes sont des mutex.

### Flux d'exécution

![Flux d'exécution mandatory](https://github.com/user-attachments/assets/6b98ec0b-cb69-4222-9a63-6f97c620065a)

### Mutex utilisés

| Mutex | Nombre | Protège |
|-------|--------|---------|
| `forks[]` | 1 par fourchette | accès exclusif à chaque fourchette |
| `meal_mutex` | 1 par philosophe | `last_meal_time` et `meals_eaten` |
| `print_mutex` | 1 global | stdout — évite les logs mélangés |
| `stop_mutex` | 1 global | flag `simulation_ended` |

### Deadlock — prévention

Si tous les philosophes prennent leur fourchette gauche simultanément, plus personne ne peut progresser. Solution : acquérir toujours les fourchettes dans l'ordre croissant des adresses mémoire.

```c
if (philo->left_fork < philo->right_fork) {
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->right_fork);
} else {
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(philo->left_fork);
}
```

Casse le cycle de dépendance circulaire — au moins un philosophe peut toujours progresser.

### Détection de mort

![Détection de mort mandatory](https://github.com/user-attachments/assets/f542b66d-6d39-4658-a7ec-3daf8dc44444)

`eat()` écrit `last_meal_time` sous `meal_mutex`. Le monitor lit `last_meal_time` sous le même mutex. Pas de race condition possible entre les deux.

### Fichiers clés

| Fichier | Rôle |
|---------|------|
| `main.c` | orchestration principale |
| `init.c` | allocation + init mutex/fourchettes |
| `routine.c` | boucle de vie des philosophes |
| `forks.c` | prise et libération des fourchettes |
| `monitor.c` | thread monitor — détection mort + repas |
| `print.c` | affichage protégé par `print_mutex` |
| `time.c` | `gettimeofday()` + `ft_usleep` précis |

---

## Partie bonus — processus + sémaphores

Un processus par philosophe. Mémoire isolée — toute la communication passe par des sémaphores nommés dans `/dev/shm`. Chaque processus contient deux threads internes : `monitor_thread` et `stop_thread`.

### Flux d'exécution

![Flux d'exécution bonus](https://github.com/user-attachments/assets/78cbaed5-0c71-4bd5-b4fe-6b8c627851ef)

### Sémaphores globaux

| Sémaphore | Init | Rôle |
|-----------|------|------|
| `SEM_FORKS` | `nb_philos` | pool de fourchettes disponibles |
| `SEM_SEATS` | `nb_philos − 1` | limite les philos pouvant tenter de manger |
| `SEM_PRINT` | `1` | mutex pour stdout |

### Sémaphores individuels (1 par philosophe)

| Sémaphore | Init | Rôle |
|-----------|------|------|
| `meal_sem` | `1` | protège `last_meal_time` et `meals_eaten` |
| `stop_sem` | `0` | signal d'arrêt — débloque `stop_thread` |

### Deadlock — prévention

`SEM_SEATS` limite à `nb_philos − 1` le nombre de philosophes qui peuvent **tenter** de prendre des fourchettes simultanément.

```c
void take_forks(t_philo *philo)
{
    sem_wait(seats_sem);   // au plus N-1 philosophes en compétition
    sem_wait(forks_sem);   // fourchette 1
    sem_wait(forks_sem);   // fourchette 2
}

void put_down_forks(t_philo *philo)
{
    sem_post(forks_sem);
    sem_post(forks_sem);
    sem_post(seats_sem);
}
```

Avec 5 philosophes et 4 sièges : 4 philosophes prennent chacun 1 fourchette, il reste 1 fourchette libre, au moins 1 peut manger, libère 2 fourchettes → cascade de déblocage.

### Détection de mort et propagation

```c
// Monitor thread (dans le processus qui détecte la mort)
while (!stop) {
    sem_wait(meal_sem);
    time = last_meal_time;
    sem_post(meal_sem);

    if (now - time > time_to_die) {
        stop = 1;
        print_status("died");
        signal_stop(data);   // poste tous les stop_sem
        return;
    }
}

// signal_stop() — réveille tous les stop_thread
for (int i = 0; i < nb_philos; i++)
    sem_post(philos[i].stop_sem);

// Stop thread (dans les autres processus)
sem_wait(stop_sem);   // bloqué jusqu'ici
stop = 1;             // déclenche l'arrêt
```

### Pas de data race inter-processus

Chaque philosophe est un processus avec sa propre copie mémoire. `data->stop` du processus 1 est indépendant de `data->stop` du processus 2. La seule communication passe par les sémaphores, gérés par l'OS.

### Fichiers clés

| Fichier | Rôle |
|---------|------|
| `main_bonus.c` | `fork()` + `waitpid()` |
| `init_bonus.c` | sémaphores globaux + par philosophe |
| `routine_bonus.c` | routine d'un philosophe |
| `monitor_bonus.c` | détection de mort dans chaque processus |
| `forks_bonus.c` | prise/libération des fourchettes |
| `cleanup_bonus.c` | `signal_stop()` + cleanup |
| `print_bonus.c` | affichage protégé par `SEM_PRINT` |

---

## Questions d'évaluation

### Mandatory

| Question | Réponse | Où dans le code |
|----------|---------|-----------------|
| 1 thread par philosophe ? | Oui | `create_philosophers()` — 1 `pthread_create` par philo |
| 1 fourchette par philosophe ? | Oui | `forks[]` de taille `nb_philos` |
| 1 mutex par fourchette ? | Oui | chaque `forks[i]` est un `pthread_mutex_t` |
| Output non mélangé ? | Oui | `print_status()` protégé par `print_mutex` |
| Protection mange/mort ? | Oui | `eat()` écrit sous `meal_mutex`, monitor lit sous le même |

### Bonus

| Question | Réponse | Où dans le code |
|----------|---------|-----------------|
| 1 processus par philosophe, parent attend ? | Oui | `fork()` dans `create_processes()`, parent dans `waitpid()` |
| 1 sémaphore global pour les fourchettes ? | Oui | `SEM_FORKS` — sémaphore de comptage |
| Output non mélangé ? | Oui | `SEM_PRINT` — un seul affichage à la fois |
| Protection mange/mort ? | Oui | `meal_sem` protège `last_meal_time` ; mort → `signal_stop()` |

---

## Notions à apprendre

### Concepts fondamentaux

- [ ] Processus vs threads — mémoire partagée ou isolée
- [ ] Mutex vs sémaphore — binaire vs comptage
- [ ] Data race — définition et prévention
- [ ] Deadlock — stratégies d'évitement (lock-ordering, N−1 seats)

### Synchronisation

- [ ] Protection de section critique (mutex, sémaphore)
- [ ] Synchronisation de l'affichage
- [ ] Communication inter-processus (sémaphores nommés)

### Fonctions système

- [ ] `fork()`, `waitpid()`, `exit()`
- [ ] `pthread_create()`, `pthread_join()`
- [ ] `pthread_mutex_lock()`, `pthread_mutex_unlock()`, `pthread_mutex_destroy()`
- [ ] `sem_open()`, `sem_wait()`, `sem_post()`, `sem_close()`, `sem_unlink()`
- [ ] `gettimeofday()`

### Nettoyage des ressources

- [ ] `pthread_mutex_destroy()` pour chaque mutex
- [ ] `sem_close()` dans tous les processus, `sem_unlink()` seulement dans le parent
- [ ] `free()` de toute la mémoire allouée
- [ ] Vérification avec Valgrind

---

## Commandes utiles

### Build

```bash
make -C philo
make -C philo_bonus
make -C philo re
make -C philo_bonus re
```

### Run

```bash
# ./philo nb_philos time_to_die time_to_eat time_to_sleep [nb_meals]

./philo 5 800 200 200          # simulation infinie
./philo 5 800 200 200 7        # s'arrête après 7 repas chacun
./philo_bonus 5 800 200 200
./philo_bonus 5 800 200 200 7
```

### Tests de référence

```bash
# ne doit pas mourir
./philo 5 800 200 200
./philo 4 410 200 200

# doit mourir
./philo 4 310 200 100
./philo 1 800 200 200    # 1 seul philo — ne peut pas manger

# charge
./philo 200 800 200 200
./philo_bonus 200 800 200 200
```

### Valgrind

```bash
# mandatory
valgrind --leak-check=full --show-leak-kinds=all \
  ./philo 5 800 200 200 7

# bonus — trace les processus enfants
valgrind --leak-check=full --show-leak-kinds=all \
  --track-fds=yes --trace-children=yes \
  ./philo_bonus 5 800 200 200 7

# vérifier les sémaphores résiduels
ls /dev/shm | grep philo
rm /dev/shm/philo_*          # si des fichiers restent
```

---

## Problèmes courants

**Data race détecté (Helgrind/TSan)**
Protéger tous les accès à `last_meal_time` et `meals_eaten` par `meal_mutex`/`meal_sem`. Protéger `simulation_ended`/`stop` par `stop_mutex`.

**Deadlock — programme bloqué**
Mandatory : vérifier l'ordre de prise des fourchettes par adresse.
Bonus : vérifier que `seats_sem` est initialisé à `nb_philos − 1`.

**Messages mélangés**
Tout `printf` doit être sous `print_mutex` (mandatory) ou `SEM_PRINT` (bonus).

**`sem_open: File exists`**
Appeler `sem_unlink()` dans `cleanup_data()`. Vérifier avec `ls /dev/shm`.

---

## Ressources

- [ByteByteGo — Process vs Thread](https://bytebytego.com/guides/what-is-the-difference-between-process-and-thread/)
- [ByteByteGo — Process Communication on Linux](https://bytebytego.com/guides/how-do-processes-talk-to-each-other-on-linux/)
- [CodeQuoi — Threads, Mutex et programmation concurrente](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/)
- [Eric Lo — Synchronization with Semaphores](https://eric-lo.gitbook.io/synchronization/semaphore-in-c)
- `man pthread_create`, `man pthread_mutex_lock`, `man sem_open`, `man fork`, `man waitpid`
- Dijkstra, E.W. (1965) — *Cooperating Sequential Processes*
