/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:26:21 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/04/16 14:06:39 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (ft_check_args(argc, argv))
		return (1);
	data = ft_data_init(argv);
	if (!data)
		return (1);
	ft_run_simulation(data);
	ft_safe_exit(data);
	return (0);
}
