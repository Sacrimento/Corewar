/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:36:15 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/04 15:12:17 by mfonteni         ###   ########.fr       */
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
 * - Define a definitive data structure for instructions
 *
**/

#include "../include/corewar.h"

int		live(t_instr instr)
{
	t_champ *thischamp;

	if (!instr.vm || !instr.vm->champ
	|| !(thischamp = get_champ_by_num(instr.vm->champ,
	bytetoint(&instr.vm->map[instr.process->pc + 1], 4))))
		return (0);
	thischamp->lives++;
	instr.process->alive++;
	instr.vm->lives++;
	ft_printf("[%d] - {BLUE}Champion %s(id:%d) is alive{EOC}",
		thischamp->lives, thischamp->name, thischamp->id);
	return (1);
}

int		ld(t_instr instr)
{
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 1) || instr.params[1].value > REG_NUMBER)
		return (0);
	if (instr.params[0].type == 4)
		instr.process->reg[instr.params[1].value] = instr.params[0].value;
	else if (instr.params[0].value < MEM_SIZE)
		instr.process->reg[instr.params[1].value]
		= bytetoint(&instr.vm->map[instr.params[0].value], 4);
	else
		return (0);
	instr.process->carry = instr.process->reg[instr.params[1].value] == 0;
	return (1);
}
/*
int lld(t_vm *vm)
{
	if ((params[1]).type != REG_CODE
	|| !(instr.params[0].type == IND_CODE
	|| instr.params[0].type == DIR_CODE))
		return (-1);
	if (instr.params[0].value == 0)
		return (instr.process->carry = 0);
	if (instr.params[0].type == IND_CODE)
		*(int*)(params[1]).address
		= vm->map[instr.params[0].value % MEM_SIZE];
	else
		*(int*)(params[1]).address = instr.params[0].value;
	return (instr.process->carry = 1);
}

int st(t_vm *vm, t_instr.process *instr.process)
{
	if (instr.params[0]->type != T_REG)
		return (instr.process->carry = 0);
	*reg2 = *reg1;
	return (instr.process->carry = 1);
}


int aff(t_vm *vm, t_instr.process *instr.process)
{
	if (instr.params[0].value > REG_NUMBER || !instr.params[0].is_reg)
		return (instr.process->carry = 0);
	//check if !char is the same NUL from the subject
	if (!instr.process->reg[instr.params[0].value])
		return (instr.process->carry = 1);
	ft_printf("%s", instr.process->reg[instr.params[0].value] % 256);
	return (instr.process->carry = 0);
}

//
int fork()
{

}

int lfork()
{
	
}

int st()
{
	
} */