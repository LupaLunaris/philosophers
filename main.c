/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:59:22 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/01/28 13:04:34 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_data	*g_data;

void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        pthread_mutex_lock(&g_data->death_lock);
        g_data->someone_died = true;
        pthread_mutex_unlock(&g_data->death_lock);
        return;
    }
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (error(RED "Wrong input:\n" WHT "	Usage:\n"
				GRN "	./philo  number_of_philosophers  time_to_die  "
				"time_to_eat  time_to_sleep  [num_times_each_philo_must_eat]\n"
				"ex:	./philo 5 800 200 200\n" RST));
	g_data = &data;
	signal(SIGINT, signal_handler);
	if (init_data(&data, argv))
		return (1);
	if (start_simulation(&data))
		return (clean_exit(&data), 1);
	clean_exit(&data);
	return (0);
}
