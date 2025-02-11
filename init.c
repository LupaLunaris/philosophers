/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:01:18 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/11 15:40:42 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_mutexes(t_state *state)
{
	int	i;

	state->forks = malloc(sizeof(pthread_mutex_t) * state->philo_count);
	if (!state->forks)
		return (1);
	i = 0;
	while (i < state->philo_count)
	{
		if (pthread_mutex_init(&state->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&state->write_lock, NULL))
		return (1);
	if (pthread_mutex_init(&state->stop_lock, NULL))
		return (1);
	return (0);
}

int	init_state(t_state *state, int argc, char **argv)
{
	state->philo_count = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	state->meals_to_eat = -1;
	if (argc == 6)
		state->meals_to_eat = ft_atoi(argv[5]);
	if (state->philo_count < 1 || state->time_to_die < 0
		|| state->time_to_eat < 0 || state->time_to_sleep < 0)
		return (1);
	state->stop_simulation = 0;
	state->threads_done = 0;
	if (pthread_mutex_init(&state->end_lock, NULL))
		return (1);
	return (create_mutexes(state));
}

int	init_philosophers(t_state *state)
{
	int	i;

	state->start_time = get_current_time();
	state->philosophers = malloc(sizeof(t_philo) * state->philo_count);
	if (!state->philosophers)
		return (1);
	i = 0;
	while (i < state->philo_count)
	{
		state->philosophers[i].id = i + 1;
		state->philosophers[i].meals_eaten = 0;
		state->philosophers[i].last_meal = state->start_time;
		state->philosophers[i].state = state;
		if (pthread_mutex_init(&state->philosophers[i].meal_lock, NULL))
			return (1);
		state->philosophers[i].left_fork = &state->forks[i];
		state->philosophers[i].right_fork = &state->forks[(i + 1)
			% state->philo_count];
		i++;
	}
	return (0);
}
