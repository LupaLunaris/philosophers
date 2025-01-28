/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:00:25 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/01/27 20:36:04 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_monitor(void *arg)
{
	t_data		*data;
	int			i;
	long long	time_since_meal;

	data = (t_data *)arg;
	accurate_sleep(1);
	while (1)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			pthread_mutex_lock(&data->death_lock);
			time_since_meal = get_time() - data->philos[i].last_meal;
			if (time_since_meal > data->time_to_die)
			{
				print_status(data, data->philos[i].id, RED "died" RST);
				data->someone_died = true;
				pthread_mutex_unlock(&data->death_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&data->death_lock);
		}
		accurate_sleep(1);
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
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (0);
}

