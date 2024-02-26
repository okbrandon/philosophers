/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:11:36 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/26 11:42:45 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Used to check if the current string is containing
 *  only digits.
 * 
 * @param str				- string to check
 * @return bool				- returns its validity
 */
static bool	ft_is_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Used to verify the validity of each argument
 * 
 * @param argc				- argc from main program
 * @param argv				- argv from main program
 * @return bool				- true if problem found
 */
bool	ft_check_args(int argc, char **argv)
{
	int	i;

	if (argc < 5)
		return (ft_error("not enough arguments", 1));
	if (argc > 6)
		return (ft_error("too many arguments", 1));
	i = 1;
	while (i < argc)
	{
		if (!ft_is_valid(argv[i]))
			return (ft_error("some arguments aren't valid", 0));
		if (i == 5)
		{
			if (ft_atoi(argv[i]) < 0)
				return (ft_error("some arguments aren't valid", 0));
		}
		else if (ft_atoi(argv[i]) <= 0)
			return (ft_error("some arguments aren't valid", 0));
		i++;
	}
	return (false);
}

/**
 * @brief Used to parse each argument after verification
 * 
 * @param data				- main data structure
 * @param argv				- argv from main program
 */
void	ft_parse_args(t_data *data, char **argv)
{
	data->size = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
}
