#  Philosophers (philo + philo_bonus)

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![42](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)
[![POSIX Threads](https://img.shields.io/badge/POSIX-Threads-1f6feb?style=for-the-badge)](https://en.wikipedia.org/wiki/Pthreads)
[![Synchronization](https://img.shields.io/badge/Synchronization-Mutexes%20%26%20Semaphores-8a2be2?style=for-the-badge)](https://en.wikipedia.org/wiki/Semaphore_(programming))
[![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=for-the-badge)](https://github.com/42School/norminette)
![Grade](https://img.shields.io/badge/Grade-125%2F100-brightgreen?style=for-the-badge)

> *"I think, therefore I am... hungry"* - Dining Philosophers

---

##  Table des matières

1. [Description du projet](#-description-du-projet)
2. [Structure du dépôt](#-structure-du-dépôt)
3. [Partie obligatoire (threads + mutex)](#-partie-obligatoire-threads--mutex)
4. [Partie bonus (processus + sémaphores)](#-partie-bonus-processus--sémaphores)
5. [Questions d'évaluation](#-questions-dévaluation-réponses-courtes)
6. [Notions à apprendre](#-notions-à-apprendre-checklist)
7. [Commandes utiles](#-commandes-utiles)
8. [Problèmes courants](#-problèmes-courants)
9. [Ressources](#-ressources)
10. [Notes importantes](#-notes-importantes)

---

##  Description du projet

### Le problème des philosophes dîneurs

Le projet **Philosophers** est une implémentation en C du célèbre problème de synchronisation créé par Edsger Dijkstra en 1965.

####  Le scénario

N philosophes sont assis autour d'une table ronde. Devant chaque philosophe se trouve un bol de spaghetti. Entre chaque paire de philosophes se trouve une fourchette (donc N fourchettes au total).

```
           🍴
      👤       👤
   🍴             🍴
      👤   🍝   👤
   🍴             🍴
      👤       👤
           🍴
```

####  Le cycle de vie d'un philosophe

Un philosophe alterne entre trois états :
1. **🤔 PENSER** : Réfléchir sur les mystères de l'univers
2. **🍝 MANGER** : Nécessite **2 fourchettes** (gauche ET droite)
3. **😴 DORMIR** : Se reposer après avoir mangé

####  Les règles

- Un philosophe doit avoir **2 fourchettes** pour manger
- Un philosophe **prend une fourchette à la fois**
- Un philosophe **pose ses fourchettes** après avoir mangé
- Les fourchettes sont des **ressources partagées** (exclusivité mutuelle)

####  Conditions d'arrêt

La simulation s'arrête quand :
- ❌ **Un philosophe meurt** : n'a pas mangé pendant `time_to_die` millisecondes
- ✅ **Objectif atteint** : tous les philosophes ont mangé `nb_meals` fois (optionnel)

####  Les défis à résoudre

1. **Deadlock (interblocage)** : Tous prennent 1 fourchette et attendent la 2e indéfiniment
2. **Race conditions** : Accès concurrent aux ressources partagées
3. **Starvation (famine)** : Un philosophe ne parvient jamais à obtenir 2 fourchettes
4. **Data races** : Lectures/écritures simultanées sur les mêmes données

###  Objectifs pédagogiques

Ce projet permet d'apprendre :

- ✅ La programmation **multi-thread** (philo) et **multi-processus** (philo_bonus)
- ✅ Les mécanismes de **synchronisation** (mutex, sémaphores)
- ✅ La gestion des **problèmes de concurrence**
- ✅ L'utilisation de la **mémoire partagée** vs **isolée**
- ✅ La **précision temporelle** en programmation système

###  Deux implémentations

| Aspect | Philo (mandatory) | Philo_bonus |
|--------|-------------------|-------------|
| Unité d'exécution | **Threads** | **Processus** |
| Mémoire | Partagée | Isolée |
| Synchronisation | Mutex | Sémaphores |
| Complexité | ⭐⭐⭐ | ⭐⭐⭐⭐ |

---

##  Structure du dépôt

```
.
├── philo/              # Partie obligatoire (threads + mutex)
│   ├── includes/
│   │   └── philo.h
│   └── srcs/
│       ├── main.c         # Point d'entrée, orchestration
│       ├── init.c         # Allocation et init des mutex
│       ├── routine.c      # Routine des philosophes
│       ├── forks.c        # Gestion des fourchettes
│       ├── monitor.c      # Détection mort + objectif
│       ├── print.c        # Affichage synchronisé
│       └── time.c         # Gestion du temps précis
│
└── philo_bonus/        # Partie bonus (processus + sémaphores)
    ├── includes/
    │   └── philo_bonus.h
    └── srcs/
        ├── main_bonus.c      # fork() + waitpid()
        ├── init_bonus.c      # Sémaphores globaux
        ├── routine_bonus.c   # Routine d'un philosophe
        ├── monitor_bonus.c   # Détection mort (par process)
        ├── forks_bonus.c     # Gestion des fourchettes
        ├── cleanup_bonus.c   # signal_stop() + cleanup
        ├── print_bonus.c     # Affichage protégé
        ├── time_bonus.c      # Gestion du temps
        ├── parsing_bonus.c   # Validation des arguments
        └── utils_bonus.c     # Utilitaires
```

---

##  Partie obligatoire (threads + mutex)

### But

Simuler N philosophes avec des **threads**. Chaque philosophe doit prendre deux fourchettes (mutex) pour manger. La simulation s'arrête quand :
- Un philosophe meurt (ne mange pas pendant `time_to_die`)
- Tous ont mangé `nb_meals` fois (optionnel)

### Fichiers clés

| Fichier | Rôle |
|---------|------|
| `main.c` | Orchestration principale |
| `init.c` | Allocation et init des mutex/fourchettes |
| `routine.c` | Routine des philosophes (boucle de vie) |
| `forks.c` | Prise et libération des fourchettes |
| `monitor.c` | Thread monitor (détection mort + repas) |
| `print.c` | Affichage protégé |
| `time.c` | Horloge + `ft_usleep` précis |

### Chemin d'exécution (flow)

```
1. main
   └─→ parse_arguments()
       └─→ init_simulation()
           ├─→ Allouer philos[]
           ├─→ Allouer forks[] (mutex)
           └─→ Initialiser tous les mutex

2. create_philosophers()
   └─→ pthread_create() × N
       └─→ Chaque thread exécute philosopher_routine()

3. create_monitor()
   └─→ pthread_create()
       └─→ Thread monitor exécute monitor_routine()

4. Boucle de chaque philosophe
   ┌──────────────────────────┐
   │ while (!simulation_ended)│
   │   think()                │
   │   take_forks()           │
   │   eat()                  │
   │   put_down_forks()       │
   │   sleep_philo()          │
   └──────────────────────────┘

5. Monitor détecte
   ├─→ Mort d'un philo → simulation_ended = 1
   └─→ Tous ont mangé → simulation_ended = 1

6. main
   ├─→ pthread_join() sur tous les threads
   └─→ cleanup() (destroy mutex, free)
```

### Synchronisation et sécurité

#### Mutex utilisés

| Mutex | Portée | Protection |
|-------|--------|------------|
| `forks[]` | 1 par fourchette | Ressource exclusive (fourchette) |
| `meal_mutex` | 1 par philosophe | `last_meal_time` et `meals_eaten` |
| `print_mutex` | Global | Affichage (évite logs mélangés) |
| `stop_mutex` | Global | `simulation_ended` |

#### Éviter le deadlock

**Problème :** Si tous les philosophes prennent leur fourchette gauche en même temps → deadlock circulaire.

**Solution :** Ordre de prise des fourchettes par **adresse mémoire** (`philo/src/forks.c`)

```c
// Toujours prendre la fourchette à l'adresse la plus petite d'abord
if (philo->left_fork < philo->right_fork) {
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->right_fork);
} else {
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(philo->left_fork);
}
```

→ Casse le cycle de dépendance circulaire.

### Mort d'un philosophe

```
Monitor Thread:
  while (!simulation_ended) {
      for each philo {
          pthread_mutex_lock(&philo->meal_mutex);
          time = philo->last_meal_time;
          pthread_mutex_unlock(&philo->meal_mutex);

          if (now - time > time_to_die) {
              pthread_mutex_lock(&stop_mutex);
              simulation_ended = 1;
              pthread_mutex_unlock(&stop_mutex);

              print_status(philo, "died");
              return;
          }
      }
  }
```

**Protection contre les data races :**
- `eat()` écrit `last_meal_time` sous `meal_mutex`
- `monitor_routine()` lit `last_meal_time` sous `meal_mutex`
- Pas de race condition possible

---

##  Partie bonus (processus + sémaphores)

### But

Simuler N philosophes avec **1 processus par philosophe**. Les fourchettes sont représentées par un seul sémaphore de comptage. Chaque processus contient 2 threads :
- `monitor_thread` : surveille la mort
- `stop_thread` : écoute le signal d'arrêt

### Fichiers clés

| Fichier | Rôle |
|---------|------|
| `main_bonus.c` | `fork()` + `waitpid()` |
| `init_bonus.c` | Sémaphores globaux + par philo |
| `routine_bonus.c` | Routine d'un philosophe |
| `monitor_bonus.c` | Détection de mort dans chaque process |
| `forks_bonus.c` | Prise/libération des fourchettes |
| `cleanup_bonus.c` | `signal_stop()` + cleanup |
| `print_bonus.c` | Affichage protégé par sémaphore |

### Sémaphores utilisés

#### Globaux (partagés par tous les processus)

| Sémaphore | Init | Rôle |
|-----------|------|------|
| `SEM_FORKS` | `nb_philos` | Pool de fourchettes disponibles |
| `SEM_SEATS` | `nb_philos - 1` | Limite les philos qui peuvent tenter de manger (anti-deadlock) |
| `SEM_PRINT` | `1` | Mutex pour l'affichage |

#### Individuels (1 par philosophe)

| Sémaphore | Init | Rôle |
|-----------|------|------|
| `meal_sem` | `1` | Protège `last_meal_time` et `meals_eaten` |
| `stop_sem` | `0` | Signal d'arrêt (réveille `stop_thread`) |

### Chemin d'exécution (flow)

#### Processus Parent

```
1. main
   └─→ parse_arguments()
       └─→ init_data()
           ├─→ sem_open(SEM_FORKS, nb_philos)
           ├─→ sem_open(SEM_SEATS, nb_philos - 1)
           ├─→ sem_open(SEM_PRINT, 1)
           └─→ Pour chaque philo:
               ├─→ sem_open(meal_sem, 1)
               └─→ sem_open(stop_sem, 0)

2. create_processes()
   └─→ fork() × N fois
       └─→ Chaque enfant exécute philosopher_routine()

3. wait_children()
   └─→ waitpid(-1, &status, 0)
       └─→ Si un enfant meurt (exit != 0):
           └─→ signal_stop() → réveille tous les autres
```

#### Processus Enfant

```
1. philosopher_routine()
   ├─→ start_stop_watcher()
   │   └─→ pthread_create(&stop_thread)
   │       └─→ sem_wait(stop_sem) ← BLOQUÉ jusqu'au signal
   │
   ├─→ start_monitor()
   │   └─→ pthread_create(&monitor_thread)
   │       └─→ Surveille last_meal_time
   │
   └─→ Boucle principale
       ┌──────────────────────┐
       │ while (!stop) {      │
       │   take_forks()       │
       │   eat()              │
       │   put_down_forks()   │
       │   sleep_philo()      │
       │   think()            │
       │ }                    │
       └──────────────────────┘

2. Si mort ou nb_meals atteint
   └─→ child_exit()
       ├─→ pthread_join(stop_thread)
       ├─→ pthread_join(monitor_thread)
       ├─→ cleanup_child()
       └─→ exit(exit_status)
```

### Éviter le deadlock (bonus)

**Problème :** Si tous les philosophes font `sem_wait(forks)` en même temps, ils prennent tous 1 fourchette → deadlock.

**Solution :** `SEM_SEATS` limite à `nb_philos - 1` le nombre de philosophes qui peuvent **tenter** de prendre des fourchettes.

```c
int take_forks(t_philo *philo)
{
    sem_wait(seats_sem);      // Max N-1 philosophes
    sem_wait(forks);          // Prendre fourchette 1
    sem_wait(forks);          // Prendre fourchette 2
    return 0;
}

void put_down_forks(t_philo *philo)
{
    sem_post(forks);          // Rendre fourchette 1
    sem_post(forks);          // Rendre fourchette 2
    sem_post(seats_sem);      // Libérer le siège
}
```

**Pourquoi ça marche ?**
- Si 5 philosophes et 4 sièges max
- 4 philosophes prennent 1 fourchette chacun
- Il reste 1 fourchette libre
- Au moins 1 des 4 peut prendre cette fourchette → mange → libère 2 fourchettes
- Cascade de déblocage

### Mort d'un philosophe (bonus)

```
Monitor Thread (dans le processus qui meurt):
  while (!stop) {
      sem_wait(meal_sem);
      time = last_meal_time;
      sem_post(meal_sem);

      if (now - time > time_to_die) {
          stop = 1;
          print_status("died");
          signal_stop(data);  // ← IMPORTANT
          return;
      }
  }

signal_stop(data):
  for (i = 0; i < nb_philos; i++) {
      sem_post(philos[i].stop_sem);  // Réveille tous les Stop Threads
  }

Stop Thread (dans les AUTRES processus):
  sem_wait(stop_sem);  // ← Se réveille quand signal_stop() appelé
  stop = 1;            // Déclenche l'arrêt du processus
  return;
```

### Pourquoi il n'y a pas de data race inter-process

**Chaque philosophe est un processus** : pas de mémoire partagée entre eux.

Les seuls objets partagés sont les **sémaphores** (gérés par l'OS dans `/dev/shm`).

- `data->stop` dans le processus 1 ≠ `data->stop` dans le processus 2 (copies indépendantes)
- Communication uniquement via sémaphores (`stop_sem`, `meal_sem`, etc.)

---

##  Questions d'évaluation (réponses courtes)

### philo (obligatoire)

| Question | Réponse | Où dans le code ? |
|----------|---------|-------------------|
| 1 thread par philosophe ? | ✅ Oui | `create_philosophers()` crée 1 thread par philo |
| 1 fourchette par philosophe ? | ✅ Oui | `forks[]` de taille `nb_philos` |
| 1 mutex par fourchette ? | ✅ Oui | Chaque `forks[i]` est un `pthread_mutex_t` |
| Output non mélangé ? | ✅ Oui | `print_status()` protégé par `print_mutex` |
| Mort + protection "mange/mort" ? | ✅ Oui | Monitor lit `last_meal_time` sous `meal_mutex`, `eat()` écrit sous le même mutex |

### philo_bonus (bonus)

| Question | Réponse | Où dans le code ? |
|----------|---------|-------------------|
| 1 processus par philosophe + parent attend ? | ✅ Oui | `fork()` dans `create_processes()`, parent fait `waitpid()` |
| 1 sémaphore global pour les fourchettes ? | ✅ Oui | `SEM_FORKS` est un sémaphore de comptage |
| Output non mélangé ? | ✅ Oui | `SEM_PRINT` garantit un seul affichage à la fois |
| Mort + protection "mange/mort" ? | ✅ Oui | `meal_sem` protège `last_meal_time` entre `eat()` et `monitor_thread`. En cas de mort : `signal_stop()` réveille tous les processus |

---

##  Notions à apprendre (checklist)

### Concepts fondamentaux

- [ ] **Processus vs threads** (mémoire partagée ou non)
- [ ] **Mutex vs sémaphore** (binaire vs comptage)
- [ ] **Data race** et comment les éviter
- [ ] **Deadlock** et stratégies d'évitement (ordre, N-1 seats)

### Synchronisation

- [ ] Protection de section critique (mutex, sémaphore)
- [ ] Synchronisation de l'affichage
- [ ] Communication inter-processus (sémaphores nommés)

### Fonctions système

- [ ] `fork()`, `waitpid()`, `exit()`
- [ ] `pthread_create()`, `pthread_join()`
- [ ] `pthread_mutex_lock()`, `pthread_mutex_unlock()`
- [ ] `sem_open()`, `sem_wait()`, `sem_post()`, `sem_close()`, `sem_unlink()`

### Gestion du temps

- [ ] `gettimeofday()` pour obtenir le timestamp
- [ ] Précision temporelle (pourquoi pas `usleep()` direct)
- [ ] Boucle d'attente avec vérification de `stop`

### Nettoyage des ressources

- [ ] `pthread_mutex_destroy()`
- [ ] `sem_close()` + `sem_unlink()`
- [ ] `free()` de toute la mémoire allouée
- [ ] Vérification avec Valgrind

---

##  Commandes utiles

### Build

```bash
# Partie obligatoire
make -C philo

# Partie bonus
make -C philo_bonus

# Clean
make -C philo clean
make -C philo_bonus clean

# Fclean
make -C philo fclean
make -C philo_bonus fclean

# Re
make -C philo re
make -C philo_bonus re
```

### Run

```bash
# Syntaxe
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

# Partie obligatoire
./philo 5 800 200 200        # Simulation infinie
./philo 5 800 200 200 7      # Chaque philo doit manger 7 fois

# Partie bonus
./philo_bonus 5 800 200 200
./philo_bonus 5 800 200 200 7
```

### Tests

```bash
# Ne doit pas mourir
./philo 5 800 200 200
./philo 4 410 200 200

# Un philosophe doit mourir
./philo 4 310 200 100
./philo 1 800 200 200        # 1 seul philo (ne peut pas manger)

# Beaucoup de philosophes
./philo 200 800 200 200
./philo_bonus 200 800 200 200

# Avec objectif
./philo 5 800 200 200 5
./philo_bonus 5 800 200 200 5
```

### Valgrind

```bash
# Partie obligatoire
valgrind --leak-check=full --show-leak-kinds=all \
  ./philo 5 800 200 200 7

# Partie bonus (important : --trace-children=yes)
valgrind --leak-check=full --show-leak-kinds=all \
  --track-fds=yes --trace-children=yes \
  ./philo_bonus 5 800 200 200 7
```

### Vérifier les sémaphores résiduels

```bash
# Après exécution de philo_bonus, vérifier :
ls /dev/shm | grep philo

# Si des fichiers restent, les supprimer :
rm /dev/shm/philo_*
```

---

##  Problèmes courants

### Data race détecté

**Symptôme :** Helgrind/TSan détecte des accès concurrents

**Solution :**
- Protéger TOUS les accès à `last_meal_time` et `meals_eaten` par `meal_mutex`/`meal_sem`
- Protéger `simulation_ended`/`stop` par `stop_mutex` ou vérifier atomiquement

### Deadlock

**Symptôme :** Le programme se bloque, rien ne se passe

**Solution (philo) :**
- Ordre de prise des fourchettes par adresse

**Solution (philo_bonus) :**
- Utiliser `seats_sem` avec valeur `nb_philos - 1`

### Messages mélangés

**Symptôme :** `"42 1 is42 2 eating sleeping"`

**Solution :**
- Protéger `printf()` par `print_mutex` ou `SEM_PRINT`

### Sémaphores non nettoyés (bonus)

**Symptôme :** `sem_open: File exists`

**Solution :**
- Appeler `sem_unlink()` dans `cleanup_data()`
- Vérifier avec `ls /dev/shm`

---

## 📖 Ressources

### Différences processus/threads
- [ByteByteGo - Process vs Thread](https://bytebytego.com/guides/what-is-the-difference-between-process-and-thread/)
- [CodeQuoi - Threads, Mutex et programmation concurrente](https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/)

### Communication inter-processus
- [ByteByteGo - Process Communication on Linux](https://bytebytego.com/guides/how-do-processes-talk-to-each-other-on-linux/)

### Sémaphores
- [Eric Lo - Synchronization with Semaphores](https://eric-lo.gitbook.io/synchronization/semaphore-in-c)
- [Tala Informatique - Sémaphores en C](https://tala-informatique.fr/index.php?title=C_semaphore)

### Documentation officielle
- [man pthread_create](https://man7.org/linux/man-pages/man3/pthread_create.3.html)
- [man pthread_mutex_lock](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- [man sem_open](https://man7.org/linux/man-pages/man3/sem_open.3.html)
- [man fork](https://man7.org/linux/man-pages/man2/fork.2.html)
- [man waitpid](https://man7.org/linux/man-pages/man2/waitpid.2.html)

---

##  Notes importantes

### Différences clés obligatoire vs bonus

| Aspect | Obligatoire (philo) | Bonus (philo_bonus) |
|--------|---------------------|---------------------|
| **Unité d'exécution** | Threads | Processus |
| **Mémoire** | Partagée | Isolée (copies) |
| **Synchronisation** | Mutex | Sémaphores nommés |
| **Fourchettes** | `pthread_mutex_t forks[]` | `sem_t *forks` (comptage) |
| **Anti-deadlock** | Ordre de prise | `seats_sem = N-1` |
| **Monitor** | 1 thread global | 1 thread par processus |
| **Communication** | Variables partagées | Sémaphores (`stop_sem`) |

### Points d'attention

⚠️ **philo (obligatoire) :**
- Toujours détruire les mutex (`pthread_mutex_destroy`)
- Un seul thread monitor pour tous les philosophes
- Ordre de prise des fourchettes crucial

⚠️ **philo_bonus :**
- Faire `sem_close()` dans TOUS les processus
- Faire `sem_unlink()` seulement dans le parent
- Utiliser `--trace-children=yes` avec Valgrind
- Chaque processus a son propre `monitor_thread` et `stop_thread`

---

**Bon appétit philosophique ! 🍝🍴**

