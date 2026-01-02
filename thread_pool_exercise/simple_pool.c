/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_pool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 10:46:31 by jodde             #+#    #+#             */
/*   Updated: 2026/01/02 12:09:02 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define THREAD_NUM 8
int shutdown_pool = 0;

typedef struct s_task
{
	int	a;
	int	b;
}	t_task;

t_task	taskQueue[256];
int	taskCount = 0;
pthread_mutex_t	mutexQueue;
pthread_cond_t	condQueue;

void	execute(t_task *task)
{
	int	result = task->a + task->b;
	printf("the sum of %d and %d is %d\n", task->a, task->b, result);
}

void	*start_task(void *args)
{
	t_task	task;
	int	i;

	(void) args;
	while(1)
	{
		pthread_mutex_lock(&mutexQueue);
		if (shutdown_pool && taskCount == 0)
        {
			printf("Thread %lu is shutting down\n", pthread_self());
            pthread_mutex_unlock(&mutexQueue);
            break;
        }
		while(taskCount == 0)
			pthread_cond_wait(&condQueue, &mutexQueue);
		
		task = taskQueue[0];
		for (i = 0; i < taskCount - 1; i++)
			taskQueue[i] = taskQueue[i + 1];
		taskCount--;	
		pthread_mutex_unlock(&mutexQueue);
		execute(&task);
	}
	return (NULL);
}

void	submit_task(t_task task)
{	
	if (taskCount < 256)
	{ 
		pthread_mutex_lock(&mutexQueue);
		taskQueue[taskCount++] = task;
		pthread_cond_signal(&condQueue);
		pthread_mutex_unlock(&mutexQueue);
	}
	else
		printf("Task queue is full, cannot submit new task\n");
}

int	main(int argc, char *argv[])
{
	int             i;
	t_task		t;
	pthread_t       th[THREAD_NUM];
	
	(void) argc;
	(void) argv;   
	pthread_mutex_init(&mutexQueue, NULL);
	pthread_cond_init(&condQueue, NULL);
	for(i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_create(&th[i], NULL, &start_task, NULL) != 0)
			perror("failed to createee the thread");
	}
	srand(time(NULL));
	for(i = 0; i < 100; i++)
	{
		t = (t_task){ .a = rand() % 100, .b = rand() % 100};
		submit_task(t);
	}
	pthread_mutex_lock(&mutexQueue);
	shutdown_pool = 1;
	pthread_cond_broadcast(&condQueue);
	pthread_mutex_unlock(&mutexQueue);
	for (i = 0; i < THREAD_NUM; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("failed to join thread");
	}
	pthread_mutex_destroy(&mutexQueue);
	pthread_cond_destroy(&condQueue);
	return (0);
}
