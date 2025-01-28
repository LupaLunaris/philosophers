/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:01:18 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/01/28 13:04:10 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_data *data)
{
	int	i;

	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->death_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	data->forks = malloc(sizeof(t_mutex) * data->philo_count);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void	init_philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	data->start_time = get_time();
	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].left_fork_id = i;
		data->philos[i].right_fork_id = (i + 1) % data->philo_count;
		if (i % 2)
		{
			data->philos[i].left_fork = &data->forks[i];
			data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
		}
		else
		{
			data->philos[i].left_fork = &data->forks[(i + 1) % data->philo_count];
			data->philos[i].right_fork = &data->forks[i];
		}
		data->philos[i].data = data;
		i++;
	}
}

int	init_data(t_data *data, char **argv)
{
	data->philo_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat = -1;
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	if (data->philo_count < 1 || data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0 || (argv[5] && data->must_eat < 0))
		return (error(MAG "Invalid arguments: > 0\n" RST));
	if (data->time_to_die < 60)
		return (error(MAG "Time to die must be at least 60ms\n" RST));
	if (data->time_to_eat < 60)
		return (error(MAG "Time to eat must be at least 60ms\n" RST));
	if (data->time_to_sleep < 60)
		return (error(MAG "Time to sleep must be at least 60ms\n" RST));
	data->someone_died = false;
	init_mutexes(data);
	init_philosophers(data);
	return (0);
}
