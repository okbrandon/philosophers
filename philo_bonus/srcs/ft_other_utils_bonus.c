/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:09:26 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/04/18 12:27:39 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

/**
 * @brief Used to display an error message and help if needed.
 * 
 * @param message				- message to display
 * @param help_needed			- display help or not
 * @return int					- EXIT_FAILURE status code
 */
int	ft_error(char *message, int help_needed)
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
 * @brief Used to print each action of a philosopher.
 * This will wait a dedicated semaphore to write messages, print it
 *  and then post the semaphore to prevent mixed up messages.
 * 
 * @param data				- pointer to main data structure
 * @param id				- id of philosopher to display its action
 * @param action			- action to display
 * @param do_unlock			- post the write semaphore or not (TRUE or FALSE)
 */
void	ft_print_action(t_data *data, int id, char *action, int do_unlock)
{
	long	start_time_to_ms;

	sem_wait(data->print_sem);
	if (DO_PRINT)
	{
		start_time_to_ms = (data->start_time.tv_sec * 1000) + \
			(data->start_time.tv_usec / 1000);
		if (id >= 0)
			printf("%-6ld %6d %s\n", \
				ft_timestamp() - start_time_to_ms, id, action);
		else
			printf("%-11ld %s\n", \
				ft_timestamp() - start_time_to_ms, action);
	}
	if (do_unlock)
		sem_post(data->print_sem);
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

	(void) data;
	if (time > 0)
	{
		end_time = ft_timestamp() + time;
		while ((unsigned int) ft_timestamp() < end_time)
			usleep(data->size * 2);
	}
}

/**
 * @brief Used to free each allocated part of the main data structure.
 * It'll also close each opened semaphore.
 * 
 * @param data				- pointer to main data structure
 */
void	ft_safe_exit(t_data *data)
{
	int	i;
	int	return_value;

	waitpid(-1, &return_value, 0);
	if (data->must_eat != 0 && \
		(WIFEXITED(return_value) || WIFSIGNALED(return_value)))
	{
		i = -1;
		data->is_simulating = FALSE;
		sem_post(data->total_ate_sem);
		while (++i < data->size)
			kill(data->philosophers[i]->pid, SIGTERM);
	}
	i = -1;
	while (++i < data->size)
	{
		sem_close(data->philosophers[i]->eat_sem);
		free(data->philosophers[i]);
	}
	free(data->philosophers);
	free(data);
	sem_close(data->print_sem);
	sem_close(data->forks_sem);
	sem_close(data->total_ate_sem);
}
