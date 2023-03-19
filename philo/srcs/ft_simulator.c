/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:35:58 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/03/19 12:58:50 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	ft_run_eat_check(t_data *data, long difference, int i)
{	
	int	j;

	j = 0;
	while (i < data->size)
	{
		if (!data->philosophers->done_eating[j])
			break ;
		j++;
	}
	if (j >= data->size)
	{
		ft_print_action(data, -1, DONE_EATING, FALSE);
		pthread_mutex_unlock(&data->var_modification);
		return (1);
	}
	if (data->must_eat > 0 && \
		!data->philosophers->done_eating[i] && difference <= 1)
	{
		if (++data->philosophers->total_ate[i] >= data->must_eat)
			data->philosophers->done_eating[i] = TRUE;
	}
	return (0);
}

static void	ft_handle_philo_eat(t_data *data, int i)
{
	pthread_mutex_lock(&data->philosophers->forks[i]);
	ft_print_action(data, (i + 1), TOOK_FORK, TRUE);
	pthread_mutex_lock(&data->philosophers->forks[(i + 1) % data->size]);
	ft_print_action(data, (i + 1), TOOK_FORK, TRUE);
	ft_print_action(data, (i + 1), EATING, TRUE);
	pthread_mutex_lock(&data->var_modification);
	data->philosophers->last_meal[i] = (ft_timestamp() - data->start_time);
	pthread_mutex_unlock(&data->var_modification);
	ft_usleep(data->time_to_eat, data);
	pthread_mutex_unlock(&data->philosophers->forks[i]);
	pthread_mutex_unlock(&data->philosophers->forks[(i + 1) % data->size]);
}

static void	ft_handle_philo_life(t_data *data)
{
	static int	i;
	int			current_i;

	pthread_mutex_lock(&data->philo_life_init);
	current_i = i++;
	pthread_mutex_unlock(&data->philo_life_init);
	if (current_i % 2)
		ft_usleep(100, data);
	while (!data->philosophers->done_eating[current_i])
	{
		ft_handle_philo_eat(data, current_i);
		pthread_mutex_lock(&data->var_read);
		if (!data->is_simulating)
			return ;
		pthread_mutex_unlock(&data->var_read);
		ft_print_action(data, (current_i + 1), SLEEPING, TRUE);
		ft_usleep(data->time_to_sleep, data);
		ft_print_action(data, (current_i + 1), THINKING, TRUE);
	}
}

void	ft_run_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->size)
	{
		if (pthread_create(&data->philosophers->threads[i], NULL, \
				(void *) ft_handle_philo_life, data) != 0)
		{
			ft_error("thread creation has failed", FALSE);
			return ;
		}
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
			pthread_mutex_lock(&data->var_modification);
			difference = (ft_timestamp() - data->start_time) \
				- data->philosophers->last_meal[i];
			if (ft_run_eat_check(data, difference, i))
				return ;
			if (difference >= data->time_to_die)
			{
				ft_print_action(data, (i + 1), DIED, FALSE);
				return ;
			}
			pthread_mutex_unlock(&data->var_modification);
		}
		ft_usleep(1, data);
	}
	pthread_mutex_lock(&data->print_mutex);
}
