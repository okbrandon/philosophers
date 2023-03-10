/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:07:25 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/03/10 19:57:01 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_display_params(t_data *data)
{
	if (!data)
		return ;
	printf("%s%sphilosophers %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		data->size, RESET);
	printf("%s%stime_to_die %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		data->time_to_die, RESET);
	printf("%s%stime_to_eat %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		data->time_to_eat, RESET);
	printf("%s%stime_to_sleep %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		data->time_to_sleep, RESET);
	printf("%s%smust_eat %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		data->must_eat, RESET);
	printf("%s%sstart_time %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		data->start_time, RESET);
	printf("%s%sinitialization took %s%dms\n", RED, BOLD, RESET, \
		(ft_timestamp() - data->start_time));
}

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
	ft_usleep(100, data);
	ft_safe_exit(data);
	return (0);
}
