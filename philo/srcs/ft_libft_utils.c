/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:36:30 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/04/16 16:49:35 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/**
 * @brief ASCII to Integer function right from libft.
 * 
 * @param str				- ASCII char
 * @return int				- Integer found
 */
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

/**
 * @brief calloc remake right from libft.
 * 
 * @param count				- number of items to be allocated
 * @param size				- size of elements
 * @return void*			- malloc'd items
 */
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
