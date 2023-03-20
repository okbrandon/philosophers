/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:07:25 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/03/20 11:29:38 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* 	printf("%s%sjust left all threads%s\n", GREEN, BOLD, RESET);
	ft_usleep(100, data);
	printf("%s%severything has been left carefully%s\n", GREEN, BOLD, RESET);*/
int	main(int argc, char **argv)
{
	t_data			*data;

	if (ft_check_args(argc, argv))
		return (1);
	data = ft_data_init(argv);
	if (!data)
		return (1);
	data->philosophers = ft_philosophers_init(data);
	if (!data->philosophers)
		return (1);
	ft_run_simulation(data);
	ft_run_death_checker(data);
	ft_safe_exit(data);
	return (0);
}
