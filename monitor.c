/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:00:25 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/01/28 13:08:27 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_ate_enough(t_data *data)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	if (data->must_eat == -1)
		return (0);
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->meal_lock);
		if (data->philos[i].meals_eaten >= data->must_eat)
			finished++;
		pthread_mutex_unlock(&data->meal_lock);
		i++;
	}
	return (finished == data->philo_count);
}

int	check_philosopher_death(t_data *data, int i)
{
	pthread_mutex_lock(&data->death_lock);
	if (get_time() - data->philos[i].last_meal > data->time_to_die)
	{
		print_status(data, data->philos[i].id, RED "died" RST);
		data->someone_died = true;
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->death_lock);
	return (0);
}

int	check_simulation_end(t_data *data)
{
	pthread_mutex_lock(&data->death_lock);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->death_lock);
	return (check_all_ate_enough(data));
}

void	*death_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!check_simulation_end(data))
	{
		i = -1;
		while (++i < data->philo_count && !data->someone_died)
		{
			if (check_philosopher_death(data, i))
				return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	data->start_time = get_time();
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philosopher_routine, &data->philos[i]))
			return (error(BLU "Thread creation failed\n" RST));
		i++;
	}
	if (pthread_create(&monitor, NULL, death_monitor, data))
		return (error(BLU "Monitor thread creation failed\n" RST));
	i = -1;
	while (++i < data->philo_count)
		pthread_join(data->philos[i].thread, NULL);
	pthread_join(monitor, NULL);
	return (0);
}
