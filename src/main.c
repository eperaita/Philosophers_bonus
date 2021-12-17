/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:02:17 by eperaita          #+#    #+#             */
/*   Updated: 2021/12/17 19:17:33 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../philo.h"

static void	mom(t_table *table, pid_t *pids)
{
	int		i;

	waitpid(-1, NULL, 0);
	i = -1;
	while (++i < table->nphilo)
		kill(pids[i], SIGKILL);
}

static int	philo_childs(t_table *table)
{
	pid_t	*pids;
	int		i;

	i = -1;
	pids = (pid_t *)malloc(table->nphilo * sizeof(pid_t));
	if (!pids)
		return (1);
	gettimeofday(&table->startime, NULL);
	while (++i < table->nphilo)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			return (1);
		if (pids[i] == 0)
		{
			table->id = i;
			break ;
		}
	}
	if (pids[table->id] == 0)
		philo(table, table->id + 1);
	else
		mom(table, pids);
	free(pids);
	return (0);
}

static int	set_table(t_table *table, char **argv, int argc)
{
	table->startime.tv_sec = 0;
	table->startime.tv_usec = 0;
	table->nphilo = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	table->id = 0;
	if (table->nphilo <= 0 || table->t_die < 0
		|| table->t_eat < 0 || table->t_sleep < 0)
		return (1);
	if (argc == 6)
		table->ndinner = ft_atoi(argv[5]);
	else
		table->ndinner = 0;
	sem_unlink("sem_fork");
	sem_unlink("sem_death");
	sem_unlink("sem_print");
	table->sem_fork = sem_open("sem_fork",
			O_CREAT | O_EXCL, 0644, table->nphilo);
	table->sem_death = sem_open("sem_death",
			O_CREAT | O_EXCL, 0644, 1);
	table->sem_print = sem_open("sem_print",
			O_CREAT | O_EXCL, 0644, 1);
	return (0);
}

int	error(int error)
{
	if (error == 1)
		write(1, "Invalid arguments\n", 18);
	if (error == 2)
		write(1, "The table is not set\n", 21);
	if (error == 3)
		write(1, "Mom does not fork the philosophers\n", 35);
	return (1);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (error(1));
	if (set_table(&table, argv, argc))
		return (error(2));
	if (philo_childs(&table))
		return (error(3));
	sem_close(table.sem_fork);
	sem_close(table.sem_death);
	return (0);
}
