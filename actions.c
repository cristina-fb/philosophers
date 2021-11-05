/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 18:19:54 by crisfern          #+#    #+#             */
/*   Updated: 2021/11/05 13:37:20 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->d->mutex[philo->f1]);
	pthread_mutex_lock(&philo->d->mutex_w);
	printf("%ld %d has taken a fork\n", get_time(philo), philo->id);
	pthread_mutex_unlock(&philo->d->mutex_w);
	pthread_mutex_lock(&philo->d->mutex[philo->f2]);
	pthread_mutex_lock(&philo->d->mutex_w);
	printf("%ld %d has taken a fork\n", get_time(philo), philo->id);
	printf("%ld %d is eating\n", get_time(philo), philo->id);
	pthread_mutex_unlock(&philo->d->mutex_w);
	//gettimeofday(&philo->last_eat, NULL);
	usleep(philo->d->t_eat * 1000);
	pthread_mutex_unlock(&philo->d->mutex[philo->f1]);
	pthread_mutex_unlock(&philo->d->mutex[philo->f2]);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->d->mutex_w);
	printf("%ld %d is sleeping\n", get_time(philo), philo->id);
	pthread_mutex_unlock(&philo->d->mutex_w);
	usleep(philo->d->t_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->d->mutex_w);
	printf("%ld %d is thinking\n", get_time(philo), philo->id);
	pthread_mutex_unlock(&philo->d->mutex_w);
}

void	*actions(void *p)
{
	t_philo			*philo;

	philo = (t_philo *)p;
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (0);
}
