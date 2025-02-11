/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 14:00:05 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/02/11 15:53:47 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	smart_sleep(long duration)
{
	long	start;
	long	current;

	start = get_current_time();
	while (1)
	{
		current = get_current_time();
		if (current - start >= duration)
			break ;
		usleep(100);
	}
}

void	print_status(t_philo *philo, char *status)
{
	if (!simulation_should_stop(philo->state))
	{
		pthread_mutex_lock(&philo->state->write_lock);
		printf("%ld %d %s\n" RST,
			get_current_time() - philo->state->start_time,
			philo->id, status);
		pthread_mutex_unlock(&philo->state->write_lock);
	}
}

int	simulation_should_stop(t_state *state)
{
	int	stop;

	pthread_mutex_lock(&state->stop_lock);
	stop = state->stop_simulation;
	pthread_mutex_unlock(&state->stop_lock);
	return (stop);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str > 8 && *str < 14))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
