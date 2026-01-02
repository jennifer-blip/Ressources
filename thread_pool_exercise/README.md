Description

Ce projet est un exercice d’apprentissage visant à comprendre le concept de thread pool en langage C.
Le code permet de :

- Créer un pool fixe de threads utilisant l’API POSIX (pthread)
- Soumettre des tâches simples (addition de deux entiers)
- Exécuter les tâches de manière concurrente par les threads du pool
- Gérer correctement la synchronisation à l’aide de mutex et condition variables
- Arrêter proprement les threads une fois que toutes les tâches ont été exécutées

L’objectif de cet exercice est de se familiariser avec :
- La gestion de threads en C
- Les primitives de synchronisation (pthread_mutex_t, pthread_cond_t)
- La communication entre threads et la gestion d’une queue de tâches

Compilation

- Pour compiler le code, utilisez gcc avec l’option -pthread :
gcc -Wall -Wextra -Werror -pthread simple_pool.c -o simple_pool

Utilisation

- Après compilation, lancez simplement le programme :
./simple_pool
- Le programme crée un pool de threads, génère 100 tâches aléatoires et les exécute en parallèle.
- Chaque tâche calcule la somme de deux nombres aléatoires et affiche le résultat.

Concepts abordés

- Thread Pool : utilisation d’un nombre fixe de threads pour exécuter plusieurs tâches de façon concurrente.
- Queue de tâches : les tâches sont stockées dans un tableau partagé entre les threads.
- Mutex : protection de l’accès concurrent à la queue.
- Condition variable : permet aux threads de s’endormir quand la queue est vide et de se réveiller quand de nouvelles tâches sont soumises.
- Shutdown propre : arrêt contrôlé des threads après exécution de toutes les tâches.

Fichiers

- simple_pool.c : code source principal

Limitations / améliorations possibles

- Queue implémentée comme tableau simple (une queue circulaire serait plus efficace)
- Tâches générées aléatoirement, pas d’input utilisateur
- Peut être étendu pour un thread pool réutilisable et dynamique

Auteur / Référence

- Exercice réalisé pour l’apprentissage des thread pools en C, inspiré par CodeVault – Thread Pools in C, 6 janvier 2001
- Lien : https://www.google.com/url?sa=t&source=web&rct=j&opi=89978449&url=https://www.youtube.com/watch%3Fv%3D_n2hE2gyPxU&ved=2ahUKEwjnid6mx-yRAxXoNvsDHQZrG_EQ3aoNegQIFBA1&usg=AOvVaw1A4ZsvRdiGFa9tXaRMfy_9
