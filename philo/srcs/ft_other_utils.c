/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:13:35 by bsoubaig          #+#    #+#             */
/*   Updated: 2024/02/26 12:02:20 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief Used to display an error message and help if needed.
 * 
 * @param message				- message to display
 * @param help_needed			- display help or not
 * @return int					- EXIT_FAILURE status code
 */
int	ft_error(char *message, bool help_needed)
{
	printf("%s%s%sAn error occurred: %s%s\n", \
		RESET, RED, BOLD, RESET, message);
	if (help_needed)
		printf("---\n%s%s[%s%s?%s%s]%s Need help?\n%s»%s%s»%s%s»%s %s\n", \
			RESET, BOLD, RED, BOLD, RESET, BOLD, \
			RESET, BOLD, RED, BOLD, RESET, BOLD, RESET, COMMAND);
	return (EXIT_FAILURE);
}

/**
 * @brief Used to print each action of a philosopher.
 * This will lock a mutex dedicated to write messages, print it
 *  and then unlock to prevent mixed up messages.
 * 
 * @param data				- pointer to main data structure
 * @param id				- id of philosopher to display its action
 * @param action			- action to display
 * @param is_death			- is the action death (true or false)
 */
void	ft_print_action(t_data *data, int id, char *action, bool is_death)
{
	pthread_mutex_lock(&data->print_mutex);
	if (ft_is_simulating(data))
	{
		if (id >= 0)
			printf("%-6ld %6d %s\n", \
				ft_timestamp() - data->start_time, id, action);
		else
			printf("%-11ld %s\n", \
				ft_timestamp() - data->start_time, action);
	}
	else if (is_death)
		printf("%-6ld %6d %s\n", \
			ft_timestamp() - data->start_time, id, action);
	pthread_mutex_unlock(&data->print_mutex);
}

/**
 * @brief Adjusted usleep function.
 * 
 * @param time				- time to sleep in millis
 * @param data				- pointer to main data structure
 */
void	ft_usleep(unsigned int time, t_data *data)
{
	unsigned int	end_time;

	if (time > 0)
	{
		end_time = ft_timestamp() + time;
		while ((unsigned int) ft_timestamp() < end_time)
			usleep(data->size * 2);
	}
}

/**
 * @brief Used to free each allocated part of the main data structure.
 * It'll also destroy each mutex.
 * 
 * @param data				- pointer to main data structure
 */
void	ft_safe_exit(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->var_modification);
	pthread_mutex_destroy(&data->var_read);
	pthread_mutex_destroy(&data->sim_read);
	pthread_mutex_destroy(&data->philo_life_init);
	i = 0;
	while (i < data->size)
	{
		free(data->philosophers->hands[i]);
		pthread_mutex_destroy(&data->philosophers->forks[i]);
		pthread_detach(data->philosophers->threads[i]);
		i++;
	}
	free(data->philosophers->forks);
	free(data->philosophers->hands);
	free(data->philosophers->done_eating);
	free(data->philosophers->last_meal);
	free(data->philosophers->total_ate);
	free(data->philosophers->threads);
	free(data->philosophers);
	free(data);
}
