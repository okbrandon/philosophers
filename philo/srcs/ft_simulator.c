/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:35:58 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/03/09 18:38:06 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_must_eat_handler(t_data *data, int i)
{
	int	total;

	total = data->philosophers->total_ate[i] + 1;
	if (data->must_eat != -1 && total > data->must_eat && i == 0)
	{
		data->is_simulating = 0;
		return ;
	}
	pthread_mutex_lock(&data->var_modification);
	data->philosophers->total_ate[i]++;
	pthread_mutex_unlock(&data->var_modification);
}

static void	ft_philo_life_cycle(t_data *data, int i)
{
	pthread_mutex_lock(&data->philosophers->forks[i]);
	ft_print_action(data, (i + 1), TOOK_FORK, TRUE);
	pthread_mutex_lock(&data->philosophers->forks[(i + 1) % data->size]);
	ft_print_action(data, (i + 1), TOOK_FORK, TRUE);
	ft_print_action(data, (i + 1), EATING, TRUE);
	data->philosophers->last_meal[i] = (ft_timestamp() - data->start_time);
	ft_usleep(data->time_to_eat, data);
	pthread_mutex_unlock(&data->philosophers->forks[i]);
	pthread_mutex_unlock(&data->philosophers->forks[(i + 1) % data->size]);
	ft_print_action(data, (i + 1), SLEEPING, TRUE);
	ft_must_eat_handler(data, i);
	ft_usleep(data->time_to_sleep, data);
	ft_print_action(data, (i + 1), THINKING, TRUE);
}

static void	ft_handle_philo_life(t_data *data)
{
	int	i;

	i = data->current_philo_id;
	pthread_mutex_unlock(&data->philo_life_init);
	if (i % 2)
		ft_usleep(1, data);
	while (!data->is_there_a_dead)
		ft_philo_life_cycle(data, i);
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
		i = 0;
		while (i < data->size)
		{
			difference = (ft_timestamp() - data->start_time) \
				- data->philosophers->last_meal[i];
			if (difference >= data->time_to_die)
			{
				data->is_there_a_dead = 1;
				ft_print_action(data, (i + 1), DIED, FALSE);
				return ;
			}
			i++;
		}
		ft_usleep(1, data);
	}
	pthread_mutex_lock(&data->print_mutex);
	printf("everyone's done eating.\n");
}
