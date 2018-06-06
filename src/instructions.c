/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:36:15 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/06 11:52:01 by abouvero         ###   ########.fr       */
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
 * - Ask about the right thing to do with carry
 * (differences between epictech & 42 subjects)
 * 
 *
**/

#include "../include/corewar.h"

int		live(t_instr instr)
{
	t_champ *thischamp;

	if (!instr.vm || !instr.vm->champ
	|| !(thischamp = get_champ_by_num(instr.vm->champ,
	bytetoint(&instr.vm->map[instr.process->pc + 1], 4))))
		return (decal_pc(instr.process, T_DIR, 0));
	thischamp->lives++;
	instr.process->alive++;
	instr.vm->lives++;
	instr.vm->last = thischamp;
	ft_printf("[%d] - {BLUE}Champion %s(id:%d) is alive{EOC}",
		thischamp->lives, thischamp->name, thischamp->id);
	return (decal_pc(instr.process, T_DIR, 1));
}

int		ld(t_instr instr)
{
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x02)
	|| instr.params[1].value > REG_NUMBER)
		return (free_params(instr, 0));
	if (instr.params[0].type == T_DIR)
		instr.process->reg[instr.params[1].value] = instr.params[0].value;
	else
		instr.process->reg[instr.params[1].value]
		= bytetoint(&instr.vm->map
		[get_address(instr.process->pc + (instr.params[0].value % IDX_MOD))],
		T_DIR);
	instr.process->carry = instr.process->reg[instr.params[1].value] == 0;
	return (free_params(instr, 1));
}

int		st(t_instr instr)
{
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x03)
	|| instr.params[0].value > REG_NUMBER)
		return (free_params(instr, 0));
	if (instr.params[1].type == T_REG && instr.params[1].value <= REG_NUMBER)
		instr.process->reg[instr.params[1].value]
		= instr.process->reg[instr.params[0].value];
	else if (instr.params[1].type == T_IND)
		inttobytes(instr.vm->map
		[get_address(instr.process->pc + (instr.params[1].value % IDX_MOD))],
		instr.vm->map);
	else
		return (free_params(instr, 0));
	instr.process->carry = instr.params[0].value == 0;
	return (free_params(instr, 1));
}

int add(t_instr instr)
{
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x04)
	|| instr.params[0].value > REG_NUMBER
	|| instr.params[1].value > REG_NUMBER
	|| instr.params[2].value > REG_NUMBER)
		return (free_params(instr, 0));
	instr.process->reg[instr.params[2].value]
	= instr.params[0].value + instr.params[1].value;
	instr.process->carry = instr.process->reg[instr.params[2].value] == 0;
	return (free_params(instr, 1));
}

int sub(t_instr instr)
{
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x05)
	|| instr.params[0].value > REG_NUMBER
	|| instr.params[1].value > REG_NUMBER
	|| instr.params[2].value > REG_NUMBER)
		return (free_params(instr, 0));
	instr.process->reg[instr.params[2].value]
	= instr.params[0].value - instr.params[1].value;
	instr.process->carry = instr.process->reg[instr.params[2].value] == 0;
	return (free_params(instr, 1));
}

int and(t_instr instr)
{
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x06)
	|| instr.params[2].value > REG_NUMBER)
		return (free_params(instr, 0));
	convert_params(instr, 2);
	instr.process->reg[instr.params[2].value]
	= instr.params[0].value & instr.params[1].value;
	instr.process->carry = instr.process->reg[instr.params[2].value] == 0;
	return (free_params(instr, 1));
}

int or(t_instr instr)
{
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x07)
	|| instr.params[2].value > REG_NUMBER)
		return (free_params(instr, 0));
	convert_params(instr, 2);
	instr.process->reg[instr.params[2].value]
	= instr.params[0].value | instr.params[1].value;
	instr.process->carry = instr.process->reg[instr.params[2].value] == 0;
	return (free_params(instr, 1));
}

int xor(t_instr instr)
{
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x08)
	|| instr.params[2].value > REG_NUMBER)
		return (free_params(instr, 0));
	convert_params(instr, 2);
	instr.process->reg[instr.params[2].value]
	= instr.params[0].value ^ instr.params[1].value;
	instr.process->carry = instr.process->reg[instr.params[2].value] == 0;
	return (free_params(instr, 1));
}
//TODO: Check this one :
int zjmp(t_instr instr)
{
	if (instr.process->carry == 0)
		return (decal_pc(instr.process, T_IND, 0));
	instr.process->pc = get_address(
		bytetoint(&instr.vm->map[instr.process->pc + 1], 2));
	return (1);
}

int ldi(t_instr instr)
{
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x0a)
	|| instr.params[2].value > REG_NUMBER)
		return (free_params(instr, 0));
	convert_params(instr, 2);
	instr.process->reg[instr.params[2].value]
	= instr.params[0].value + instr.params[1].value;

}



int		lld(t_instr instr)
{
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x0d)
	|| instr.params[1].value > REG_NUMBER)
		return (0);
	if (instr.params[0].type == T_DIR)
		instr.process->reg[instr.params[1].value] = instr.params[0].value;
	else
		instr.process->reg[instr.params[1].value]
		= bytetoint(&instr.vm->map[(instr.process->pc
		+ instr.params[0].value) % MEM_SIZE], T_DIR);
	instr.process->carry = instr.process->reg[instr.params[1].value] == 0;
	return (1);
}

