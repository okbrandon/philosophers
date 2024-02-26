/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulator_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 11:23:18 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/26 11:41:29 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Used to get the current timestamp in millis.
 * 
 * @return long				- timestamp in millis
 */
long	ft_timestamp(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

/**
 * @brief Used to get the simulation status without any race problem.
 * 
 * @param data              - pointer to the main data structure 
 * @return bool             - true or false, if simulation is running 
 */
bool	ft_is_simulating(t_data *data)
{
	bool    simulating;

	pthread_mutex_lock(&data->sim_read);
	simulating = data->is_simulating;
	pthread_mutex_unlock(&data->sim_read);
	return (simulating);
}

/**
 * @brief Used to update the simulation status without any race problem. 
 * 
 * @param data              - pointer to the main data structure
 * @param status            - new simulation status
 */
void	ft_update_simulation(t_data *data, bool status)
{
	pthread_mutex_lock(&data->sim_read);
	data->is_simulating = status;
	pthread_mutex_unlock(&data->sim_read);
}

void	ft_wait_for_threads(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->var_modification);
		if (data->threads_done >= data->size)
		{
			pthread_mutex_unlock(&data->var_modification);
			break ;
		}
		pthread_mutex_unlock(&data->var_modification);
		ft_usleep(100, data);
	}
}
