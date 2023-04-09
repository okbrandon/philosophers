/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsoubaig <bsoubaig@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 10:26:21 by bsoubaig          #+#    #+#             */
/*   Updated: 2023/04/10 00:04:20 by bsoubaig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/* sem_t	*g_semaphore;
int		g_to_log;

void	*ft_job(void *args)
{
	int	i;

	i = *(int *) args;
	printf("[%d] is waiting in the queue\n", i);
	sem_wait(g_semaphore);
	printf(GREEN "[%d] logged in\n" RESET, i);
	sleep(rand() % 2 + 1);
	printf(GREY "[%d] logged out\n" RESET, i);
	printf(RED "%d people are left\n" RESET, --g_to_log);
	sem_post(g_semaphore);
	free(args);
	return (0);
}

void	ft_post_times(int times)
{
	int	i;

	i = 0;
	while (i++ < times)
		sem_post(g_semaphore);
}

int	main(void)
{
	int			i;
	int			*a;
	pthread_t	threads[14];

	i = 0;
	g_to_log = 14;
	g_semaphore = sem_open("/philo_test", O_CREAT, 0666, 1);
	ft_post_times(2);
	while (i < 14)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&threads[i], NULL, &ft_job, a) != 0)
			exit(EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < 14)
	{
		if (pthread_join(threads[i], NULL) != 0)
			exit(EXIT_FAILURE);
		i++;
	}
	sem_close(g_semaphore);
	sem_unlink("/philo_test");
	return (0);
} */

/* void	ft_segfault(int to_segfault)
{
	char	str[4];
	int		i;

	i = 0;
	if (!to_segfault)
		return ;
	while (i < 42)
	{
		str[i] = 'c';
		i++;
	}
}

int	main(void)
{
	int	pid;
	int	exit;

	pid = fork();
	if (pid == -1)
	{
		printf("Fork failure\n");
		return (1);
	}
	if (pid == 0)
	{
		printf("from child: waiting 2 seconds (%d)\n", getpid());
		sleep(2);
		ft_segfault(0);
		printf("from child: execution finished\n");
		return (42);
	}
	waitpid(pid, &exit, 0);
	if (WTERMSIG(exit) == SIGSEGV)
		printf("program has segfaulted\n");
	printf("pid=%d exit=%d\n", getpid(), WEXITSTATUS(exit));
	return (0);
} */

/**
 * Each philosopher is a process (fork)
 * 
 */
int	main(int argc, char **argv)
{
	t_data	*data;

	if (ft_check_args(argc, argv))
		return (1);
	data = ft_data_init(argv);
	if (!data)
		return (1);
	ft_run_simulation(data);
	ft_safe_exit(data);
	return (0);
}
