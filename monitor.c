/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:00:25 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/13 14:43:36 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_simulation_stop(t_state *state)
{
	pthread_mutex_lock(&state->stop_lock);
	if (!state->stop_simulation)
	{
		state->stop_simulation = 1;
		pthread_mutex_unlock(&state->stop_lock);
		return (1);
	}
	pthread_mutex_unlock(&state->stop_lock);
	return (0);
}

static int	check_death(t_state *state, t_philo *philo)
{
	long	current_time;

	pthread_mutex_lock(&philo->meal_lock);
	current_time = get_current_time();
	if (current_time - philo->last_meal >= state->time_to_die)
	{
		pthread_mutex_unlock(&philo->meal_lock);
		if (set_simulation_stop(state))
		{
			pthread_mutex_lock(&state->write_lock);
			printf("%ld %d %sdied%s\n",
				current_time - state->start_time,
				philo->id, RED, RST);
			pthread_mutex_unlock(&state->write_lock);
		}
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_lock);
	return (0);
}

static int	check_meals(t_state *state)
{
	int	i;
	int	finished_eating;

	if (state->meals_to_eat == -1)
		return (0);
	i = 0;
	finished_eating = 0;
	while (i < state->philo_count)
	{
		pthread_mutex_lock(&state->philosophers[i].meal_lock);
		if (state->philosophers[i].meals_eaten >= state->meals_to_eat)
			finished_eating++;
		pthread_mutex_unlock(&state->philosophers[i].meal_lock);
		i++;
	}
	return (finished_eating == state->philo_count);
}

void	monitor_simulation(t_state *state)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < state->philo_count)
		{
			if (check_death(state, &state->philosophers[i]))
				return ;
			if (check_meals(state))
			{
				set_simulation_stop(state);
				return ;
			}
			i++;
		}
		usleep(50);
	}
}
