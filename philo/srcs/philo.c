/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:07:25 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/03/08 10:58:14 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Main program.
 */
int	main(int argc, char **argv)
{
	t_data			*data;

	if (ft_check_args(argc, argv))
		return (EXIT_FAILURE);
	data = ft_data_init(argv);
	if (!data)
		return (EXIT_FAILURE);
	data->philosophers = ft_philosophers_init(data);
	if (!data->philosophers || !data->philosophers->hands)
		return (EXIT_FAILURE);
	ft_run_simulation(data);
	ft_run_watcher(data);
	ft_wait_for_threads(data);
	ft_safe_exit(data);
	return (EXIT_SUCCESS);
}
