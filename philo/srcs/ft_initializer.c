/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initializer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:00:45 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/03/07 11:14:54 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philosophers	*ft_philosophers_init(t_data *data)
{
	t_philosophers	*philos;
	int				i;

	philos = ft_calloc(1, sizeof(t_philosophers));
	if (!philos)
	{
		ft_error("philosophers allocation went wrong", 0);
		return (NULL);
	}
	philos->total_ate = ft_calloc(data->size, sizeof(int));
	philos->last_meal = ft_calloc(data->size, sizeof(long));
	philos->forks = ft_calloc(data->size, sizeof(pthread_mutex_t));
	i = 0;
	while (i < data->size)
	{
		pthread_mutex_init(&philos->forks[i], NULL);
		printf("philosopher's fork (%d) has been initialized\n", i + 1);
		i++;
	}
	return (philos);
}

t_data	*ft_data_init(char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
	{
		ft_error("data allocation went wrong", 0);
		return (NULL);
	}
	ft_parse_args(data, argv);
	data->start_time = ft_timestamp();
	data->is_there_a_dead = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	return (data);
}
