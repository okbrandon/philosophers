/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initializer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:00:45 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/26 10:56:25 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Used to return an initialized hands array.
 * This array contains the id of each philosopher's left and right fork.
 * 
 * @param data				- main data structure
 * @return hands**			- hands with fork ids
 */
int	**ft_hands_init(t_data *data)
{
	int	**hands;
	int	i;

	hands = ft_calloc(data->size, sizeof(int *));
	if (!hands)
		return (NULL);
	i = -1;
	while (++i < data->size)
	{
		hands[i] = ft_calloc(2, sizeof(int));
		hands[i][0] = i;
		hands[i][1] = (i + 1) % data->size;
		if (i % 2)
		{
			hands[i][0] = (i + 1) % data->size;
			hands[i][1] = i;
		}
	}
	return (hands);
}

/**
 * @brief Used to return an initialized philosophers structure.
 * This structure contains all needed data from each philosopher.
 * 
 * @param data				- main data structure
 * @return t_philosophers*	- pointer to philosophers structure
 */
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
	philos->done_eating = ft_calloc(data->size, sizeof(int));
	philos->last_meal = ft_calloc(data->size, sizeof(long));
	philos->forks = ft_calloc(data->size, sizeof(pthread_mutex_t));
	philos->threads = ft_calloc(data->size, sizeof(pthread_t));
	i = 0;
	while (i < data->size)
		pthread_mutex_init(&philos->forks[i++], NULL);
	philos->hands = ft_hands_init(data);
	return (philos);
}

/**
 * @brief Used to return an initialized data structure.
 * This structure contains all needed data from the program
 *  and also a pointer to the philosophers stucture.
 * 
 * @param argv				- argv from main program
 * @return t_data*			- pointer to data structure
 */
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
	data->current_philo_id = 0;
	data->eat_count = 0;
	data->done_eating = 0;
	data->is_simulating = 1;
	data->threads_done = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->var_modification, NULL);
	pthread_mutex_init(&data->var_read, NULL);
	pthread_mutex_init(&data->sim_read, NULL);
	pthread_mutex_init(&data->philo_life_init, NULL);
	return (data);
}
