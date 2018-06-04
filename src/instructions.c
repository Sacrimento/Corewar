/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:36:15 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/04 17:48:51 by mfonteni         ###   ########.fr       */
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
	if (!compare_params(instr.params, 0x02)
	|| instr.params[1].value > REG_NUMBER)
		return (free_params(&instr.params, 0));
		
	if (instr.params[0].type == T_DIR)
		instr.process->reg[instr.params[1].value] = instr.params[0].value;
	else if (instr.params[0].value <= MEM_SIZE)
		instr.process->reg[instr.params[1].value]
		= bytetoint(&instr.vm->map[instr.process->pc
		+ (instr.params[0].value % IDX_MOD)], T_DIR);
	else
		return (free_params(&instr.params, 0));
	instr.process->carry = instr.process->reg[instr.params[1].value] == 0;
	return (free_params(&instr.params, 1));
}

int		st(t_instr instr)
{
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x03)
	|| instr.params[0].value > REG_NUMBER)
		return (0);
	if (instr.params[1].type == T_REG && instr.params[1].value <= REG_NUMBER)
		instr.process->reg[instr.params[1].value]
		= instr.process->reg[instr.params[0].value];
	else if (instr.params[1].type == T_IND)
	{
		inttobytes(instr.vm->map[pc + (instr.params[1].value % IDX_MOD)]);
	}
	
}



int		lld(t_instr instr)
{
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x0d)
	|| instr.params[1].value > REG_NUMBER)
		return (0);
	if (instr.params[0].type == T_DIR)
		instr.process->reg[instr.params[1].value] = instr.params[0].value;
	else if (instr.params[0].value < MEM_SIZE)
		instr.process->reg[instr.params[1].value]
		= bytetoint(&instr.vm->map[instr.process->pc
		+ instr.params[0].value], T_DIR);
	else
		return (0);
	instr.process->carry = instr.process->reg[instr.params[1].value] == 0;
	return (1);
}

