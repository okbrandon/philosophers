/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args_handler_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:08:06 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/04/18 11:11:29 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/**
 * @brief Used to check if the current string is containing
 *  only digits.
 * 
 * @param str				- string to check
 * @return int				- returns its validity
 */
static int	ft_is_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/**
 * @brief Used to verify the validity of each argument
 * 
 * @param argc				- argc from main program
 * @param argv				- argv from main program
 * @return int				- 0 if no problem found
 */
int	ft_check_args(int argc, char **argv)
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
	return (FALSE);
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
