/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:09:55 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/03 11:27:06 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->data, philo->id, YEL "has taken a fork" RST);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->data, philo->id, YEL "has taken a fork" RST);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->data, philo->id, YEL "has taken a fork" RST);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->data, philo->id, YEL "has taken a fork" RST);
	}
}

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(data, philo->id, YEL "has taken a fork" RST);
		accurate_sleep(data->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	take_forks(philo);
	pthread_mutex_lock(&data->death_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&data->death_lock);
	print_status(data, philo->id, ORG "is eating" RST);
	accurate_sleep(data->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo->data, philo->id, BLU "is sleeping" RST);
	accurate_sleep(philo->data->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	print_status(philo->data, philo->id, CYN "is thinking" RST);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = get_time();
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!check_death(philo))
	{
		philo_eat(philo);
		if (philo->data->philo_count == 1)
			break ;
		if (philo->data->must_eat != -1
			&& philo->meals_eaten >= philo->data->must_eat)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
