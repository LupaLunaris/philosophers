/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:59:22 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/01/27 20:50:08 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data data;

	if (argc != 5 && argc != 6)
		return error(RED "Wrong input:\n" WHT "	Usage:\n" GRN "	./philo  number_of_philosophers  time_to_die  time_to_eat  time_to_sleep  [number_of_times_each_philosopher_must_eat]\nex:	./philo 5 800 200 200\n" RST);
	if (init_data(&data, argv))
		return 1;
	if (start_simulation(&data))
		return clean_exit(&data), 1;
	clean_exit(&data);
	return 0;
}
