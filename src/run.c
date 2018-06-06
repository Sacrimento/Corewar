/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 11:22:38 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/06 15:46:08 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static void	init_instr_tab(void)
{
	int (*instr_tab[16])(t_instr);

	instr_tab[0] = live;
	instr_tab[1] = ld;
	instr_tab[2] = st;
	instr_tab[3] = add;
	instr_tab[4] = sub;
	instr_tab[5] = and;
	instr_tab[6] = or;
	instr_tab[7] = xor;
	instr_tab[8] = zjmp;
	instr_tab[9] = ldi;
	//instr_tab[10] = sti;
	//instr_tab[11] = fork;
	instr_tab[12] = lld;
	//instr_tab[13] = lldi;
	//instr_tab[14] = lfork;
	//instr_tab[15] = aff;
	return (instr_tab);
}

static int	exec_process(t_process *process, t_vm *vm)
{
	unsigned char	opc;
	t_instr			instr;

	opc = vm->map[process->pc];
	if (opc < 1 || opc > 16)
		return (decal_pc(process, 1, 0));
	if (process->cycles_left == -1)
	{
		process->cycles_left = g_op_tab[opc - 1].nb_cycle;
		return (0);
	}
	//instr_tab[opc](instr);
	return (1);
}

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

static void	exec_processes(t_process *process, t_vm *vm)
{
	if (!process)
		return ;
	while (process)
	{
		if (process->cycles_left > 0)
			process->cycles_left--;
		else
			exec_process(process, vm);
		process = process->next;
	}
}

int			run(t_vm *vm)
{
	int		ctd;
	int		check;
	// int		(*instr_tab[16])(t_instr);

	check = 0;
	// instr_tab = init_instr_tab();
	ctd = CYCLE_TO_DIE;
	while (vm->processes_nbr)
	{
		if (vm->cycle == vm->dump)
			return (mem_dump(vm->map));
		if (!(vm->cycle % ctd) && vm->cycle)
		{
			check_process(vm);
			if (++check == MAX_CHECKS || vm->lives >= NBR_LIVE)
			{
				vm->lives = 0;
				check = 0;
				ctd -= CYCLE_DELTA;
			}
		}
		exec_processes(vm->processes, vm/*, instr_tab*/);
		vm->cycle++;
	}
	return (1);
}
