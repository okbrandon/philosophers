/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initializer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:00:45 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/02/27 15:32:49 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_parameters	ft_parameters_init(char **argv)
{
	t_parameters	param;

	ft_parse_args(&param, argv);
	param.start_time = ft_timestamp();
	param.dead = 0;
	pthread_mutex_init(&param.print_mutex, NULL);
	return (param);
}

t_philosopher	*ft_philosophers_init(t_parameters *param)
{
	t_philosopher	*philosophers;
	int				i;

	philosophers = ft_calloc(param->size, sizeof(t_philosopher));
	if (!philosophers)
	{
		ft_error("philosophers allocation went wrong", 0);
		return (NULL);
	}
	i = 0;
	while (i < param->size)
	{
		philosophers[i].id = i + 1;
		philosophers[i].total_ate = 0;
		philosophers[i].last_meal = 0;
		pthread_mutex_init(&philosophers[i].fork_mutex, NULL);
		printf("philosopher %d initialized\n", i + 1);
		i++;
	}
	return (philosophers);
}
