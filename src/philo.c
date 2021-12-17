/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:20:19 by eperaita          #+#    #+#             */
/*   Updated: 2021/12/17 19:18:03 by eperaita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "../philo.h"

static void	philos_routine(t_table *table)
{
	while (1)
	{
		if (table->group == 2)
		{
			table->group = 3;
			sleeping(table);
		}
		if (table->group == 3)
		{
			table->group = 1;
			thinking(table);
		}
		if (table->group == 1)
		{
			table->group = 2;
			eating(table);
			table->eated++;
			if (table->ndinner && (table->eated == table->ndinner))
				exit (0);
		}
	}
}

static int	my_group(t_table *table)
{
	int	group;

	group = 0;
	if (table->nphilo % 2 != 0 && table->id == table->nphilo)
		group = 3;
	else if (table->id % 2 != 0)
		group = 1;
	else if (table->id % 2 == 0)
		group = 2;
	return (group);
}

void	philo(t_table *table, int id)
{
	table->id = id;
	table->eatime = table->startime;
	table->group = my_group(table);
	table->eated = 0;
	pthread_create(&table->thread, NULL, &philo_dead, table);
	philos_routine(table);
	exit(0);
}
