/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 16:09:55 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/10 17:24:01 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	handle_one_philosopher(t_philo *philo)
{
	print_status(philo, YEL"has taken a fork");
	smart_sleep(philo->state->time_to_die);
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (philo->state->philo_count == 1)
		return (handle_one_philosopher(philo));
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, YEL"has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, YEL"has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, YEL"has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, YEL"has taken a fork");
	}
	return (0);
}

int	eating_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&philo->meal_lock);
	print_status(philo, MAG"is eating");
	smart_sleep(philo->state->time_to_eat);
	pthread_mutex_lock(&philo->meal_lock);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!simulation_should_stop(philo->state))
	{
		if (take_forks(philo))
			break ;
		if (eating_routine(philo))
			break ;
		if (philo->state->meals_to_eat != -1
			&& philo->meals_eaten >= philo->state->meals_to_eat)
			break ;
		print_status(philo, BLU"is sleeping");
		smart_sleep(philo->state->time_to_sleep);
		print_status(philo, CYN"is thinking");
	}
	pthread_mutex_lock(&philo->state->end_lock);
	philo->state->threads_done++;
	pthread_mutex_unlock(&philo->state->end_lock);
	return (NULL);
}
