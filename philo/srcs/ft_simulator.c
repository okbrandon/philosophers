/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simulator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:35:58 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/26 11:42:11 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Used to check if all philosophers are done eating or not.
 * 
 * @param data				- pointer to main data structure
 * @return int				- return if everyone's done eating (true or false)
 */
static int	ft_run_eat_checker(t_data *data)
{
	int	i;

	if (data->must_eat < 0 || data->size == 1)
		return (0);
	if (data->must_eat == 0)
		return (1);
	i = -1;
	data->done_eating = 0;
	while (++i < data->size)
	{
		pthread_mutex_lock(&data->var_read);
		data->eat_count = data->philosophers->total_ate[i];
		if (data->eat_count >= data->must_eat)
		{
			if (++data->done_eating >= data->size)
			{
				pthread_mutex_unlock(&data->var_read);
				ft_print_action(data, -1, DONE_EATING, false);
				return (1);
			}
		}
		pthread_mutex_unlock(&data->var_read);
	}
	return (0);
}

/**
 * @brief Used to run a loop that last until the simulation's done.
 * It'll check if a philosopher is far away from its last meal.
 * 
 * @param data				- pointer to main data structure
 */
void	ft_run_death_checker(t_data *data)
{
	int		i;

	while (ft_is_simulating(data))
	{
		i = -1;
		while (++i < data->size)
		{
			pthread_mutex_lock(&data->var_modification);
			if ((ft_timestamp() - data->start_time) \
				- data->philosophers->last_meal[i] > data->time_to_die)
			{
				ft_update_simulation(data, false);
				ft_print_action(data, (i + 1), DIED, true);
				break ;
			}
			if (ft_run_eat_checker(data))
			{
				ft_update_simulation(data, false);
				break ;
			}
			pthread_mutex_unlock(&data->var_modification);
		}
		ft_usleep(1, data);
	}
	pthread_mutex_unlock(&data->var_modification);
}

/**
 * @brief First philosopher's eating part. Manages the fork handling
 *  and the eating event.
 * 
 * @param data				- pointer to main data structure
 * @param i					- index of philosopher
 */
static void	ft_handle_philo_eat(t_data *data, int i)
{
	int	l_fork;
	int	r_fork;

	l_fork = data->philosophers->hands[i][0];
	r_fork = data->philosophers->hands[i][1];
	pthread_mutex_lock(&data->philosophers->forks[l_fork]);
	ft_print_action(data, (i + 1), TOOK_FORK, false);
	pthread_mutex_lock(&data->philosophers->forks[r_fork]);
	ft_print_action(data, (i + 1), TOOK_FORK, false);
	ft_print_action(data, (i + 1), EATING, false);
	pthread_mutex_lock(&data->var_modification);
	data->philosophers->last_meal[i] = (ft_timestamp() - data->start_time);
	pthread_mutex_unlock(&data->var_modification);
	ft_usleep(data->time_to_eat, data);
	pthread_mutex_lock(&data->var_modification);
	data->philosophers->total_ate[i]++;
	pthread_mutex_unlock(&data->var_modification);
	pthread_mutex_unlock(&data->philosophers->forks[r_fork]);
	pthread_mutex_unlock(&data->philosophers->forks[l_fork]);
}

/**
 * @brief Used to handle the life cycle of a philosopher.
 * 
 * @param data				- pointer to main data structure
 */
static void	ft_handle_philo_life(t_data *data)
{
	static int	i;
	int			current_i;

	pthread_mutex_lock(&data->philo_life_init);
	current_i = i++;
	pthread_mutex_unlock(&data->philo_life_init);
	if (current_i % 2)
		ft_usleep(60, data);
	while (ft_is_simulating(data))
	{
		ft_handle_philo_eat(data, current_i);
		ft_print_action(data, (current_i + 1), SLEEPING, false);
		ft_usleep(data->time_to_sleep, data);
		ft_print_action(data, (current_i + 1), THINKING, false);
	}
	pthread_mutex_lock(&data->var_modification);
	data->threads_done++;
	pthread_mutex_unlock(&data->var_modification);
}

/**
 * @brief Used to start the philosophers dining problem simulation.
 * It'll exit the simulation if it fails to create each philosopher's thread.
 * 
 * @param data				- pointer to main data stucture
 */
void	ft_run_simulation(t_data *data)
{
	int	i;

	if (data->must_eat == 0 && data->size > 1)
	{
		ft_print_action(data, -1, DONE_EATING, false);
		return ;
	}
	i = 0;
	while (i < data->size)
	{
		if (pthread_create(&data->philosophers->threads[i], NULL, \
				(void *) ft_handle_philo_life, data) != 0)
		{
			ft_error("thread creation has failed", false);
			ft_update_simulation(data, false);
			return ;
		}
		i++;
	}
}
