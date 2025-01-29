/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:59:22 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/01/29 15:30:00 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error(char *str)
{
	printf("⚠️\n	%s⚠️\n", str);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (error(RED "Wrong input:\n" WHT "	Usage:\n"
				GRN "	./philo  number_of_philosophers  time_to_die  "
				"time_to_eat  time_to_sleep  [num_times_each_philo_must_eat]\n"
				"ex:	./philo 5 800 200 200\n" RST));
	if (init_data(&data, argv))
		return (1);
	if (start_simulation(&data))
		return (clean_exit(&data), 1);
	clean_exit(&data);
	return (0);
}

/*
typedef struct	s_signal_data
{
	t_data *data;
} t_signal_data;


static void	signal_handler(int sig)
{
	t_signal_data *s_data = signal_context(NULL);
	if (sig == SIGINT)
	{
		printf("Caught SIGINT. Cleaning up...\n");
		clean_exit(s_data->data);
		ex
	}
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (error(RED "Wrong input:\n" WHT "    Usage:\n"
					GRN "   ./philo  number_of_philosophers  time_to_die  "
					"time_to_eat time_to_sleep [num_times_each_philo_must_eat]\n"
					"ex:    ./philo 5 800 200 200\n" RST));
	if (init_data(&data, argv))
		return (1);
	signal_context(&data);
	struct sigaction sa;
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		clean_exit(&data);
		return (1);
	}
	if (start_simulation(&data))
		return (clean_exit(&data), 1);
	clean_exit(&data);
	return (0);
}
*/