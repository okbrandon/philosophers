/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:13:35 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/02/24 21:51:48 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_error(char *message, int help_needed)
{
	printf("%s%s%sAn error occurred: %s%s\n", \
		RESET, RED, BOLD, RESET, message);
	if (help_needed)
		printf("%s[%s%s?%s] %s\n", RESET, RED, BOLD, RESET, COMMAND);
	return (EXIT_FAILURE);
}

int	ft_timestamp(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return ((timeval.tv_sec * 1000) + (timeval.tv_usec / 1000));
}

void	ft_safe_exit(t_parameters param)
{
	int	i;

	i = 0;
	while (i < param.size)
	{
		pthread_mutex_destroy(&param.philosophers[i].fork_mutex);
		// pthread_detach(philosophers[i].thread);
		printf("philosopher %d destroyed\n", i + 1);
		i++;
	}
	free(param.philosophers);
}
