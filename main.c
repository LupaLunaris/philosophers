/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:59:22 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/10 15:21:19 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (printf(RED"Error: Wrong number of arguments\n"RST WHT "Usage:\n"
				GRN "./philo number_of_philosophers time_to_die time_to_eat "
				"time_to_sleep [num_times_each_philo_must_eat]\n" RST
				"ex: ./philo 5 800 200 200\n" RST), 1);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				printf(RED"Error: Arguments must be numbers\n"RST);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static void	clean_simulation(t_state *state)
{
	int	i;

	pthread_mutex_lock(&state->end_lock);
	while (state->threads_done < state->philo_count)
	{
		pthread_mutex_unlock(&state->end_lock);
		usleep(1000);
		pthread_mutex_lock(&state->end_lock);
	}
	pthread_mutex_unlock(&state->end_lock);
	i = 0;
	while (i < state->philo_count)
	{
		pthread_join(state->philosophers[i].thread, NULL);
		pthread_mutex_destroy(&state->forks[i]);
		pthread_mutex_destroy(&state->philosophers[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&state->write_lock);
	pthread_mutex_destroy(&state->stop_lock);
	pthread_mutex_destroy(&state->end_lock);
	free(state->forks);
	free(state->philosophers);
}

int	main(int argc, char **argv)
{
	t_state	state;
	int		i;

	if (check_args(argc, argv))
		return (1);
	if (init_state(&state, argc, argv))
		return (1);
	if (init_philosophers(&state))
		return (1);
	i = 0;
	while (i < state.philo_count)
	{
		if (pthread_create(&state.philosophers[i].thread, NULL,
				philosopher_routine, &state.philosophers[i]))
			return (1);
		i++;
	}
	monitor_simulation(&state);
	clean_simulation(&state);
	return (0);
}
