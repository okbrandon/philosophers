/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:26:21 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/02/21 16:37:48 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_parse_args(t_parameters *param, char **argv)
{
	param->philosophers = ft_atoi(argv[1]);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		param->must_eat = ft_atoi(argv[5]);
	else
		param->must_eat = -1;
	if (param->philosophers <= 0 || param->time_to_die <= 0 \
		|| param->time_to_eat <= 0 || param->time_to_sleep <= 0)
		return (1);
	return (0);
}
