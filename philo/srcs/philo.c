/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 14:07:25 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/02/21 17:38:50 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_display_params(t_parameters *param)
{
	if (!param)
		return ;
	printf("%s%sphilosophers %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		param->philosophers, RESET);
	printf("%s%stime_to_die %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		param->time_to_die, RESET);
	printf("%s%stime_to_eat %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		param->time_to_eat, RESET);
	printf("%s%stime_to_sleep %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		param->time_to_sleep, RESET);
	printf("%s%smust_eat %s» %s%s%d%s\n", RED, BOLD, RESET, RED, BOLD, \
		param->must_eat, RESET);
}

int	main(int argc, char **argv)
{
	t_parameters	*param;

	if (ft_check_args(argc, argv))
		return (1);
	param = ft_calloc(1, sizeof(t_parameters));
	if (!param || ft_parse_args(param, argv))
		return (ft_error("allocation failed or invalid arguments", 0));
	ft_display_params(param);
	free(param);
	return (0);
}
