/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:35:58 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/03/12 11:41:04 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_run_ate_checker(t_data *data)
{
	int	i;

	if (data->is_simulating && data->must_eat > 0)
	{
		i = 0;
		while (i < data->size)
		{
			if (data->philosophers->total_ate[i] < data->must_eat)
				break ;
			i++;
		}
		if (i >= data->size)
			data->is_simulating = FALSE;
	}
}

static void	ft_handle_philo_life(t_data *data)
{
	int	i;

	i = data->current_philo_id;
	pthread_mutex_unlock(&data->philo_life_init);
	if (i % 2)
		ft_usleep(1, data);
	while (data->is_simulating)
	{
		pthread_mutex_lock(&data->philosophers->forks[i]);
		ft_print_action(data, (i + 1), TOOK_FORK, TRUE);
		pthread_mutex_lock(&data->philosophers->forks[(i + 1) % data->size]);
		ft_print_action(data, (i + 1), TOOK_FORK, TRUE);
		ft_print_action(data, (i + 1), EATING, TRUE);
		data->philosophers->last_meal[i] = (ft_timestamp() - data->start_time);
		ft_usleep(data->time_to_eat, data);
		data->philosophers->total_ate[i]++;
		pthread_mutex_unlock(&data->philosophers->forks[i]);
		pthread_mutex_unlock(&data->philosophers->forks[(i + 1) % data->size]);
		ft_run_ate_checker(data);
		if (!data->is_simulating)
			return ;
		ft_print_action(data, (i + 1), SLEEPING, TRUE);
		ft_usleep(data->time_to_sleep, data);
		ft_print_action(data, (i + 1), THINKING, TRUE);
	}
}

void	ft_run_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->size)
	{
		pthread_mutex_lock(&data->philo_life_init);
		data->current_philo_id = i;
		pthread_create(&data->philosophers->threads[i], NULL, \
			(void *) ft_handle_philo_life, data);
		i++;
	}
}

void	ft_run_death_checker(t_data *data)
{
	int		i;
	long	difference;

	while (data->is_simulating)
	{
		i = -1;
		while (++i < data->size)
		{
			difference = (ft_timestamp() - data->start_time) \
				- data->philosophers->last_meal[i];
			if (difference >= data->time_to_die)
			{
				data->is_simulating = FALSE;
				ft_print_action(data, (i + 1), DIED, FALSE);
				return ;
			}
		}
		ft_usleep(1, data);
	}
	pthread_mutex_lock(&data->print_mutex);
}
