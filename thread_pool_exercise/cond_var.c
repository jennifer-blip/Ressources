/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cond_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 13:35:43 by jodde             #+#    #+#             */
/*   Updated: 2026/01/03 13:53:33 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int fuel = 0;

void* fuel_filling(void* arg) 
{
	(void) arg;
	for (int i = 0; i < 5; i++) 
	{
		pthread_mutex_lock(&mutexFuel);
		fuel += 30;
		printf("Filled fuel... %d\n", fuel);
		pthread_mutex_unlock(&mutexFuel);
		pthread_cond_broadcast(&condFuel);
		sleep(1);
	}
	return (NULL);
}

void* car(void* arg) 
{
	(void) arg;
	pthread_mutex_lock(&mutexFuel);
	while (fuel < 40)
	{
		printf("No fuel. Waiting...\n");
        pthread_cond_wait(&condFuel, &mutexFuel);
        // Equivalent to:
        // pthread_mutex_unlock(&mutexFuel);
        // wait for signal on condFuel
        // pthread_mutex_lock(&mutexFuel);
    }
	fuel -= 40;
	printf("Car nb %lu got fuel. Now left: %d\n", pthread_self(), fuel);
	pthread_mutex_unlock(&mutexFuel);
	return (NULL);
}

int main(int argc, char* argv[]) 
{
	int i;
	
	(void) argc;
	(void) argv;
	pthread_t th[6];
	pthread_mutex_init(&mutexFuel, NULL);
	pthread_cond_init(&condFuel, NULL);
	for (i = 0; i < 6; i++)
	{
		if (i == 4 || i == 5)
		{
			if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
				perror("Failed to create thread");
		}
		else 
		{
			if (pthread_create(&th[i], NULL, &car, NULL) != 0)
				perror("Failed to create thread");
		}
    }
    for (i = 0; i < 6; i++) 
	{
        if (pthread_join(th[i], NULL) != 0)
            perror("Failed to join thread");
    }
    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return (0);
}
