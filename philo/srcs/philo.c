/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:07:25 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/02/24 21:39:48 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_display_params(t_parameters *param)
{
	if (!param)
		return ;
	printf("%s%sphilosophers %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		param->size, RESET);
	printf("%s%stime_to_die %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		param->time_to_die, RESET);
	printf("%s%stime_to_eat %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		param->time_to_eat, RESET);
	printf("%s%stime_to_sleep %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		param->time_to_sleep, RESET);
	printf("%s%smust_eat %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		param->must_eat, RESET);
	printf("%s%sstart_time %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		param->start_time, RESET);
}

int	main(int argc, char **argv)
{
	t_parameters	param;
	t_philosopher	*philosophers;

	if (ft_check_args(argc, argv))
		return (1);
	ft_parse_args(&param, argv);
	param.start_time = ft_timestamp();
	philosophers = ft_philosophers_init(&param);
	if (!philosophers)
		return (1);
	param.philosophers = philosophers;
	ft_display_params(&param);
	ft_safe_exit(param);
	return (0);
}
