/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 11:22:38 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/03 17:13:30 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static int	mem_dump(unsigned char *map)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%.2x", map[i++]);
		if (!(i % 32) && i != 0)
			ft_putchar('\n');
		else
			ft_putchar(' ');
	}
	return (1);
}

static void	exec_processes(t_process *process)
{
	if (!process)
		return ;
	while (process)
	{
		if (process->cycles_left)
			process->cycles_left--;
		else
			exec_process(process);
		process = process->next;
	}
}

int			run(t_vm *vm)
{
	int		ctd;
	int		check;

	check = 0;
	ctd = CYCLE_TO_DIE;
	while (check_process(vm->process))
	{
		if (vm->dump != -1 && vm->cycle == vm->dump - 1)
			return (mem_dump(vm->map));
		if (!(vm->cycle % ctd) && vm->cycle)
		{
			search_and_destroy_process(vm);
			if (++check == MAX_CHECK || vm->lives >= NBR_LIVE)
			{
				vm->lives = 0;
				check = 0;
				ctd -= CYCLE_DELTA;
			}
		}
		exec_processes(vm->processes);
		vm->cycle++;
	}
	return (1);
}