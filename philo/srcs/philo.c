/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:07:25 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/03/07 11:10:19 by bsoubaig         ###   ########.fr       */
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
	ft_display_params(data);
	ft_safe_exit(data);
	return (0);
}
