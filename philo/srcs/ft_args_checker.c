/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:11:36 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/02/21 15:49:34 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_is_arg_a_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

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
		if (!ft_is_arg_a_number(argv[i]))
			return (ft_error("some arguments aren't valid", 0));
		i++;
	}
	return (0);
}
