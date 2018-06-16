/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:22:38 by abouvero          #+#    #+#             */
/*   Updated: 2018/06/16 14:36:24 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

// static void	del_process(t_vm *vm, t_process *del)
// {
// 	t_process	*prev;
// 	t_process	*curr;

// 	curr = vm->processes;
// 	prev = curr;
// 	if (!curr)
// 		return ;
// 	vm->processes_nbr--;
// 	if (curr == del)
// 	{
// 		vm->processes = del->next;
// 		INFO("PROCESS ");
// 		INFONUM(del->id);
// 		INFO(" WAS KILLED!!!!!!\n");
// 		ft_memdel((void**)&del);
// 		return ;
// 	}
// 	curr = curr->next;
// 	while (curr)
// 	{
// 		if (curr == del)
// 		{
// 			prev->next = curr->next;
// 			INFO("PROCESS ");
// 			INFONUM(del->id);
// 			INFO(" WAS KILLED!!!!!!\n");
// 			ft_memdel((void**)&curr);
// 			return ;
// 		}
// 		curr = curr->next;
// 	}
// }

// void		check_process(t_vm *vm)
// {
// 	t_process *process;
// 	t_process *next;

// 	process = vm->processes;
// 	if (!process)
// 		return ;
// 	while (process)
// 	{
// 		if (!process->alive)
// 		{
// 			next = process->next;
// 			del_process(vm, process);
// 			process = next;
// 		}
// 		else
// 		{
// 			process->alive = 0;
// 			process = process->next;
// 		}
// 	}
// }

void		check_process(t_vm *vm)
{
	t_process	*pro;
	t_process	*del;

	pro = vm->processes;
	while (pro->next)
	{
		if (!pro->next->alive)
		{
			del = pro->next;
			pro->next = pro->next->next;
			ft_printf("{CYAN}PROCESS %d WAS KILLED{EOC}\n", del->id);
			ft_memdel((void**)&del);
			vm->processes_nbr -= 1;
		}
		if (pro->next)
			pro = pro->next;
	}
	ft_printf("TITI\n");
	if (!vm->processes->alive)
	{
		del = vm->processes;
		vm->processes = vm->processes->next;
		ft_printf("{CYAN}PROCESS %d WAS KILLED{EOC}\n", del->id);
		ft_memdel((void**)&del);
		vm->processes_nbr -= 1;
	}
	ft_printf("ToTo\n");
	pro = vm->processes;
	while (pro)
	{
		pro->alive = 0;
		pro = pro->next;
	}
}

int			add_process(t_vm *vm, int pc, int id)
{
	t_process	*pro;
	t_process	*new;

	static int i = 1;
	pro = vm->processes;
	if (!(new = (t_process*)ft_memalloc(sizeof(t_process))))
		return (error_mall(0));
	if (vm->processes)
		new->id = i++;
	new->alive = 1;
	new->pc = pc;
	new->carry = 0;
	new->cycles_left = -1;
	bzero((void *)new->reg, sizeof(new->reg));
	new->reg[0] = id;
	new->next = pro;
	vm->processes_nbr += 1;
	vm->processes = new;
	return (1);
}
