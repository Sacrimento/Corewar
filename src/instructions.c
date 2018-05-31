/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:36:15 by mfonteni          #+#    #+#             */
/*   Updated: 2018/05/31 16:12:20 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Toi qui passe sur ce fichier, rien n'est definitif pour l'instant,
 * j'experimente pour chercher a comprendre certains points qui sont encore
 * flous dans ma tete, la structure de données est susceptible de changer
 * encore un peu, mais l'idée est la.
 * 
 * Glosssaire :
 * OCP = Octet de Codage des Parametres
 * ***********************************************************
 * TODO: 
 * - Define a defnitive data structure for instructions
 *
**/

#include "../include/corewar.h"

int		live(t_vm *vm, t_process *process, t_param *params)
{
	t_champ *thischamp;

	if (!vm || !vm->champ
	|| !(thischamp = get_champ_by_num(vm->champ, (params[1]).value)))
		return (0);
	thischamp->lives++;
	ft_printf("[%d]{BLUE}Champion %s(id:%d) is alive{EOC}",
		thischamp->lives, thischamp->name, thischamp->id);
	return (1);
}
//not sure about this one :
int		ld(t_vm *vm, t_process *process, t_param *params)
{
	if ((params[1]).type != REG_CODE)
		return (-1);
	if (!((params[0]).type == IND_CODE
	|| (params[0]).type == DIR_CODE)
	|| (params[0]).value == 0)
		return (process->carry = 0);
	if ((params[0]).type == IND_CODE)
		*(int*)(params[1]).address
		= vm->map[((params[0]).value % IDX_MOD) % MEM_SIZE];
	else
		*(int*)(params[1]).address = (params[0]).value;
	return (process->carry = 1);
}

int lld(t_vm *vm)
{
	if ((params[1]).type != REG_CODE
	|| !((params[0]).type == IND_CODE
	|| (params[0]).type == DIR_CODE))
		return (-1);
	if ((params[0]).value == 0)
		return (process->carry = 0);
	if ((params[0]).type == IND_CODE)
		*(int*)(params[1]).address
		= vm->map[(params[0]).value % MEM_SIZE];
	else
		*(int*)(params[1]).address = (params[0]).value;
	return (process->carry = 1);
}

int st(t_vm *vm, t_process *process)
{
	if ((params[0])->type != T_REG)
		return (process->carry = 0);
	*reg2 = *reg1;
	return (process->carry = 1);
}


int aff(t_vm *vm, t_process *process)
{
	if ((params[0]).value > REG_NUMBER || !(params[0]).is_reg)
		return (process->carry = 0);
	//check if !char is the same NUL from the subject
	if (!process->reg[(params[0]).value])
		return (process->carry = 1);
	ft_printf("%s", process->reg[(params[0]).value] % 256);
	return (process->carry = 0);
}

int fork()
{

}

int lfork()
{
	
}

int st()
{
	
}