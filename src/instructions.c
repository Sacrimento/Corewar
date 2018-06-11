/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:36:15 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/11 18:26:09 by mfonteni         ###   ########.fr       */
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
 * Tests, tests, tests and another tests
**/

#include "../include/corewar.h"

int	live(t_instr instr)
{
	t_champ *thischamp;

	INFO("LIVE");
	if (!instr.vm || !instr.vm->champ
	|| !(thischamp = get_champ_by_num(instr.vm->champ,
	bytetoint(instr.vm->map, instr.process->pc + 1, 4))))
		return (decal_pc(instr.process, 4, 0));
	thischamp->lives++;
	instr.process->alive++;
	instr.vm->lives++;
	instr.vm->last = thischamp;
	ft_printf("[%d] - {BLUE}Champion %s(id:%d) is alive{EOC}",
		thischamp->lives, thischamp->name, thischamp->id);
	return (decal_pc(instr.process, 4, 1));
}

int	ld(t_instr instr)
{
	INFO("LD");
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x02)
	|| instr.params[1].value > REG_NUMBER)
		return (free_params(instr, 0));
	if (instr.params[0].type == T_DIR)
		instr.process->reg[instr.params[1].value] = instr.params[0].value;
	else
		instr.process->reg[instr.params[1].value]
		= bytetoint(instr.vm->map,
		get_address(instr.process->pc + (instr.params[0].value % IDX_MOD)), 4);
	instr.process->carry = instr.process->reg[instr.params[1].value] == 0;
	return (free_params(instr, 1));
}

int	st(t_instr instr)
{
	INFO("ST");
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x03)
	|| instr.params[0].value > REG_NUMBER)
		return (free_params(instr, 0));
	if (instr.params[1].type == T_REG && instr.params[1].value <= REG_NUMBER)
		instr.process->reg[instr.params[1].value]
		= instr.process->reg[instr.params[0].value];
	else if (instr.params[1].type == T_IND)
		inttobytes(instr.process->reg[instr.params[0].value],
		get_address(instr.process->pc + (instr.params[1].value % IDX_MOD)),
		instr.vm->map);
	else
		return (free_params(instr, 0));
	instr.process->carry = instr.params[0].value == 0;
	SUCCESS("ST SUCCESS");
	return (free_params(instr, 1));
}

int	add(t_instr instr)
{
	INFO("ADD");
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

int	sub(t_instr instr)
{
	INFO("SUB");
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

int	and(t_instr instr)
{
	INFO("AND");
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

int	or(t_instr instr)
{
	INFO("OR");
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

int	xor(t_instr instr)
{
	INFO("XOR");
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
int	zjmp(t_instr instr)
{
	INFO("ZJMP");
	if (instr.process->carry == 0)
		return (decal_pc(instr.process, 2, 0));
	instr.process->pc = get_address(
		bytetoint(instr.vm->map, instr.process->pc + 1, 2));
	return (1);
}

int	ldi(t_instr instr)
{
	INFO("LDI");
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x0a)
	|| instr.params[2].value > REG_NUMBER)
		return (free_params(instr, 0));
	convert_params(instr, 2);
	instr.process->reg[instr.params[2].value]
	= instr.vm->map[get_address((instr.process->pc
	+ (instr.params[0].value + instr.params[1].value)) % IDX_MOD)];
	instr.process->carry = instr.process->reg[instr.params[2].value] == 0;
	return (free_params(instr, 1));
}

int	sti(t_instr instr)
{
	mem_dump(instr.vm->map);
	INFO("STI");
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x0b)
	|| instr.params[0].value > REG_NUMBER)
		return (free_params(instr, 0));
	convert_params_start(instr, 1, 3);
	inttobytes(instr.process->reg[instr.params[0].value],
	get_address((instr.params[1].value + instr.params[2].value) % IDX_MOD),
	instr.vm->map);
	instr.process->carry = instr.process->reg[instr.params[0].value] == 0;
	mem_dump(instr.vm->map);
	return (free_params(instr, 1));
}

int	core_fork(t_instr instr)
{
	int i;

	i = -1;
	INFO("CORE_FORK");
	add_process(instr.vm, get_address(instr.process->pc +
	(bytetoint(instr.vm->map, instr.process->pc + 1, 2) % IDX_MOD)),
	instr.process->reg[1]);
	instr.vm->processes->carry = instr.process->carry;
	instr.vm->processes->alive = instr.process->alive;
	while (++i <= REG_NUMBER)
		instr.vm->processes->reg[i] = instr.process->reg[i];
	return (decal_pc(instr.process, 2, 1));
}

int	lld(t_instr instr)
{
	INFO("LLD");
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x0d)
	|| instr.params[1].value > REG_NUMBER)
		return (free_params(instr, 0));
	if (instr.params[0].type == T_DIR)
		instr.process->reg[instr.params[1].value] = instr.params[0].value;
	else
		instr.process->reg[instr.params[1].value]
		= bytetoint(instr.vm->map,
		get_address(instr.process->pc + instr.params[0].value), 4);
	instr.process->carry = instr.process->reg[instr.params[1].value] == 0;
	return (free_params(instr, 1));
}

int	lldi(t_instr instr)
{
	INFO("LLDI");
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x0e)
	|| instr.params[2].value > REG_NUMBER)
		return (free_params(instr, 0));
	convert_params_unrestrained(instr, 2);
	instr.process->reg[instr.params[2].value]
	= instr.vm->map[get_address(instr.process->pc
	+ (instr.params[0].value + instr.params[1].value))];
	return (free_params(instr, 1));
}

int	core_lfork(t_instr instr)
{
	int i;

	i = -1;
	INFO("CORE_LFORK");
	add_process(instr.vm, get_address(instr.process->pc +
	bytetoint(instr.vm->map, instr.process->pc + 1, 2)),
	instr.process->reg[1]);
	instr.vm->processes->carry = instr.process->carry;
	instr.vm->processes->alive = instr.process->alive;
	while (++i <= REG_NUMBER)
		instr.vm->processes->reg[i] = instr.process->reg[i];
	return (decal_pc(instr.process, 2, 1));
}

int	aff(t_instr instr)
{
	INFO("AFF");
	instr.params = get_params(instr.vm, instr.process);
	if (!compare_params(instr.params, 0x10)
	|| instr.params[0].value > REG_NUMBER
	|| !get_champ_by_num(instr.vm->champ, instr.process->reg[1]))
		return (free_params(instr, 0));
	ft_printf("{CYAN}[%d] - %s:%c{EOC}\n", instr.process->reg[1],
	get_champ_by_num(instr.vm->champ, instr.process->reg[1])->name,
	instr.process->reg[instr.params[0].value]);
	instr.process->carry = instr.process->reg[instr.params[0].value] == 0;
	return (free_params(instr, 1));
}