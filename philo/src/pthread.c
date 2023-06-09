/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdeeyien <sukitd@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 08:13:14 by sdeeyien          #+#    #+#             */
/*   Updated: 2023/06/07 17:14:30 by sdeeyien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_odd(void *args)
{
	int	n_eat;
	int	id;
	t_philo	*ptr_philo;
	int	n_philo;

	ptr_philo = (t_philo *) args;
	id = ptr_philo->id;
	n_eat = ptr_philo->philo_prop.n_eat;
	n_philo = ptr_philo->philo_prop.n_philo;
	while (n_eat)
	{
		if (ptr_philo->forks[id - 1] == 0)
		{
			pthread_mutex_lock(&(ptr_philo->ptr_mutex_forks[id - 1]));
			ptr_philo->forks[id - 1] = id;
			printf("Philo %d taken forks %d\n", id, id);
			if (ptr_philo->forks[id % n_philo] == 0)
			{
				pthread_mutex_lock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
				ptr_philo->forks[id % n_philo] = id;
				if (n_philo %2 == 0)
					printf("Philo %d taken forks %d\n", id, id + 1);
				else
					printf("Philo %d taken forks %d\n", id, (id % n_philo) + 1);
				printf("Philo %d is eating\n", id);
				sleep(1);
				n_eat--;
				ptr_philo->forks[id % n_philo] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
				ptr_philo->forks[id - 1] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id - 1]));
			}
		}
		else if (ptr_philo->forks[id - 1] == id)
		{
			if (ptr_philo->forks[id % n_philo] == 0)
			{
				pthread_mutex_lock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
				ptr_philo->forks[id % n_philo] = id;
				if (n_philo %2 == 0)
					printf("Philo %d taken forks %d\n", id, id + 1);
				else
					printf("Philo %d taken forks %d\n", id, (id % n_philo) + 1);
				printf("Philo %d is eating\n", id);
				sleep(1);
				n_eat--;
				ptr_philo->forks[id % n_philo] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
				ptr_philo->forks[id - 1] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id - 1]));
			}
		}
	}
	return (NULL);
}

void *philo_even(void *args)
{
	int	n_eat;
	int	id;
	t_philo	*ptr_philo;
	int		n_philo;

	ptr_philo = (t_philo *) args;
	id = ptr_philo->id;
	n_eat = ptr_philo->philo_prop.n_eat;
	n_philo = ptr_philo->philo_prop.n_philo;
	while (n_eat)
	{
		if (ptr_philo->forks[id % n_philo] == 0)
		{
			pthread_mutex_lock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
			ptr_philo->forks[id % n_philo] = id;
			printf("Philo %d taken forks %d\n", id, (id % n_philo) + 1);
			if (ptr_philo->forks[id - 1] == 0)
			{
				pthread_mutex_lock(&(ptr_philo->ptr_mutex_forks[id - 1]));
				ptr_philo->forks[id - 1] = id;
				printf("Philo %d taken forks %d\n", id, id);
				printf("Philo %d is eating\n", id);
				sleep(1);
				n_eat--;
				ptr_philo->forks[id - 1] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id - 1]));
				ptr_philo->forks[id % n_philo] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
			}
		}
		else if(ptr_philo->forks[id % n_philo] == id)
		{
			if (ptr_philo->forks[id - 1] == 0)
			{
				pthread_mutex_lock(&(ptr_philo->ptr_mutex_forks[id - 1]));
				ptr_philo->forks[id - 1] = id;
				printf("Philo %d taken forks %d\n", id, id);
				printf("Philo %d is eating\n", id);
				sleep(1);
				n_eat--;
				ptr_philo->forks[id - 1] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id - 1]));
				ptr_philo->forks[id % n_philo] = 0;
				pthread_mutex_unlock(&(ptr_philo->ptr_mutex_forks[id % n_philo]));
			}
		}
	}
	return (NULL);
}
