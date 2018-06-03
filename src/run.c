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

static void	exec_processes(t_process *process)
{
	if (!process)
		return ;
	while (process)
	{
		exec_process(process);
		process = process->next;
	}
}

void		run(t_vm *vm)
{
	int		ctd;
	int		check;

	check = 0;
	ctd = CYCLE_TO_DIE;
	while (check_process(vm->process))
	{
		if (!(vm->cycle % ctd) && vm->cycle)
		{
			search_and_destroy_process(vm);
			if (++check == MAX_CHECK)
			{
				check = 0;
				ctd -= CYCLE_DELTA;
			}
		}
		exec_processes(vm->processes);
		vm->cycle++;
	}
}