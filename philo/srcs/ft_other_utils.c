/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:13:35 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/02/21 16:32:31 by bsoubaig         ###   ########.fr       */
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

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;
	size_t	i;

	if (size && SIZE_MAX / size < count)
		return (NULL);
	pointer = (void *) malloc(count * size);
	if (!pointer)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		*(unsigned char *)(pointer + i) = 0;
		i++;
	}
	return (pointer);
}
