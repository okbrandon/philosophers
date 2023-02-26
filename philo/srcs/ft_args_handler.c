/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:11:36 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/02/24 20:52:12 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5)
		return (ft_error("not enough arguments", 1));
	if (argc > 6)
		return (ft_error("too much arguments", 1));
	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
			return (ft_error("some arguments aren't valid", 0));
		i++;
	}
	return (0);
}

void	ft_parse_args(t_parameters *param, char **argv)
{
	param->size = ft_atoi(argv[1]);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		param->must_eat = ft_atoi(argv[5]);
	else
		param->must_eat = -1;
}
