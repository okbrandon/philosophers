/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:24:05 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/04/01 18:16:43 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

# define RED 			"\033[0;31m"
# define PURPLE 		"\033[38;5;141m"
# define GREY 			"\033[38;5;240m"
# define GREEN 			"\033[38;5;46m"
# define RESET 			"\033[0m"
# define BOLD 			"\033[1m"

# define COMMAND		"./philo [<philo_num>] [<time_to_die>] [<time_to_eat>] \
[<time_to_sleep>] (<times_each_philo_must_eat>)"
# define TOOK_FORK		"has taken a fork"
# define EATING			"is eating"
# define SLEEPING		"is sleeping"
# define THINKING		"is thinking"
# define DIED			"died"
# define DONE_EATING	"philosophers are done eating"

# define TRUE		1
# define FALSE		0

# define EAT_SEM_NAME	"/sem_eat"
# define WRITE_SEM_NAME	"/sem_write"
# define FORKS_SEM_NAME	"/sem_forks"

# define DO_PRINT	TRUE

typedef struct s_philo
{
	pid_t			pid;
	int				id;
	int				last_meal;
	sem_t			*eat_sem;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				start_time;
	int				size;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	sem_t			*print_sem;
	sem_t			*eat_sem;
	sem_t			*forks_sem;
	struct s_philo	**philosophers;
}				t_data;

/* initializer */
t_data	*ft_data_init(char **argv);

/* args handler */
int		ft_check_args(int argc, char **argv);
void	ft_parse_args(t_data *data, char **argv);

/* other utils */
int		ft_error(char *message, int help_needed);
int		ft_timestamp(void);
void	ft_print_action(t_data *data, int id, char *action, int do_unlock);
void	ft_usleep(unsigned int time, t_data *data);

/* libft utils */
int		ft_atoi(char *str);
void	*ft_calloc(size_t count, size_t size);

#endif