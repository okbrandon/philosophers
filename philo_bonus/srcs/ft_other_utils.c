/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 14:09:26 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/04/01 18:16:25 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

int	ft_timestamp(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

void	ft_print_action(t_data *data, int id, char *action, int do_unlock)
{
	sem_wait(data->print_sem);
	if (DO_PRINT)
	{
		if (id >= 0)
			printf("%-6d %6d %s\n", \
				ft_timestamp() - data->start_time, id, action);
		else
			printf("%-11d %s\n", \
				ft_timestamp() - data->start_time, action);
	}
	if (do_unlock)
		sem_post(data->print_sem);
}

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
