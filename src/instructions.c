/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:36:15 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/25 17:43:36 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int	live(t_instr instr)
{
	t_champ *thischamp;

	if (!instr.vm->visu)
		ft_printf("attempting live for %d\n", byte_to_int(instr.vm->map, instr.process->pc + 1, 4));
	instr.process->alive = 1;
	instr.vm->lives++;
	if (!instr.vm || !instr.vm->champ
	|| !(thischamp = get_champ_by_num(instr.vm->champ,
	byte_to_int(instr.vm->map, instr.process->pc + 1, 4))))
		return (decal_pc(instr, 5, 0));
	thischamp->lives++;
	instr.vm->last = thischamp;
	!instr.vm->visu ? ft_printf("Player %d (%s) is said to be alive\n",
	thischamp->id, thischamp->name) : 0;
	return (decal_pc(instr, 5, 1));
}

int	ld(t_instr instr)
{
	get_params(&instr);
	if (!compare_params(instr.params, instr.opcode)
	|| !valid_reg(--instr.params[1].value))
		return (free_params(instr, 0));
	if (instr.params[0].type == T_DIR)
		instr.process->reg[instr.params[1].value] = instr.params[0].value;
	else
		instr.process->reg[instr.params[1].value]
		= byte_to_int(instr.vm->map,
		get_address(instr.process->pc + (instr.params[0].value % IDX_MOD)), 4);
	if (!instr.vm->visu)
		ft_printf("{YELLOW}LD loaded %d in register %d{EOC}\n",
		instr.process->reg[instr.params[1].value], instr.params[1].value);
	instr.process->carry = instr.process->reg[instr.params[1].value] == 0;
	return (free_params(instr, 1));
}

int	st(t_instr instr)
{
	get_params(&instr);
	if (!compare_params(instr.params, instr.opcode)
	|| !valid_reg(--instr.params[0].value))
		return (free_params(instr, 0));
	if (instr.params[1].type == T_REG && instr.params[1].value <= REG_NUMBER
	&& valid_reg(instr.params[1].value - 1))
	{
		instr.params[1].value--;
		instr.process->reg[instr.params[1].value]
		= instr.process->reg[instr.params[0].value];
	}
	else if (instr.params[1].type == T_IND)
		int_to_bytes(instr.process->reg[instr.params[0].value],
		get_address(instr.process->pc + (instr.params[1].value % IDX_MOD)),
		instr.vm->map, instr);
	else
		return (free_params(instr, 0));
	if (!instr.vm->visu)
		ft_printf("ST stored %d from register %d, at address %d\n",
		instr.process->reg[instr.params[0].value],
		instr.params[0].value,
		get_address(instr.process->pc + (instr.params[1].value % IDX_MOD)));
	return (free_params(instr, 1));
}

int	add(t_instr instr)
{
	get_params(&instr);
	if (!compare_params(instr.params, instr.opcode)
	|| !valid_reg(--instr.params[0].value)
	|| !valid_reg(--instr.params[1].value)
	|| !valid_reg(--instr.params[2].value))
		return (free_params(instr, 0));
	instr.process->reg[instr.params[2].value]
	= instr.process->reg[instr.params[0].value]
	+ instr.process->reg[instr.params[1].value];
	instr.process->carry = instr.process->reg[instr.params[2].value] == 0;
	return (free_params(instr, 1));
}

int	sub(t_instr instr)
{
	get_params(&instr);
	if (!compare_params(instr.params, instr.opcode)
	|| !valid_reg(--instr.params[0].value)
	|| !valid_reg(--instr.params[1].value)
	|| !valid_reg(--instr.params[2].value))
		return (free_params(instr, 0));
	instr.process->reg[instr.params[2].value]
	= instr.process->reg[instr.params[0].value]
	- instr.process->reg[instr.params[1].value];
	instr.process->carry = instr.process->reg[instr.params[2].value] == 0;
	return (free_params(instr, 1));
}

int	and(t_instr instr)
{
	get_params(&instr);
	if (!compare_params(instr.params, instr.opcode)
	|| !valid_reg(--instr.params[2].value) || !convert_params(&instr, 2))
		return (free_params(instr, 0));
	instr.process->reg[instr.params[2].value]
	= instr.params[0].value & instr.params[1].value;
	instr.process->carry = instr.process->reg[instr.params[2].value] == 0;
	return (free_params(instr, 1));
}

int	or(t_instr instr)
{
	get_params(&instr);
	if (!compare_params(instr.params, instr.opcode)
	|| !valid_reg(--instr.params[2].value) || !convert_params(&instr, 2))
		return (free_params(instr, 0));
	instr.process->reg[instr.params[2].value]
	= instr.params[0].value | instr.params[1].value;
	instr.process->carry = instr.process->reg[instr.params[2].value] == 0;
	return (free_params(instr, 1));
}

int	xor(t_instr instr)
{
	get_params(&instr);
	if (!compare_params(instr.params, instr.opcode)
	|| !valid_reg(--instr.params[2].value) || !convert_params(&instr, 2))
		return (free_params(instr, 0));
	instr.process->reg[instr.params[2].value]
	= instr.params[0].value ^ instr.params[1].value;
	instr.process->carry = instr.process->reg[instr.params[2].value] == 0;
	return (free_params(instr, 1));
}

int	zjmp(t_instr instr)
{
	if (instr.process->carry == 0)
		return (decal_pc(instr, 3, 0));
	instr.process->pc = get_address(instr.process->pc +
		byte_to_int(instr.vm->map, instr.process->pc + 1, 2) % IDX_MOD);
	instr.process->cycles_left = -1;
	return (decal_pc(instr, 0, 1));
}

int	ldi(t_instr instr)
{
	get_params(&instr);
	if (!compare_params(instr.params, instr.opcode)
	|| !valid_reg(--instr.params[2].value) || !convert_params(&instr, 2))
		return (free_params(instr, 0));
	instr.process->reg[instr.params[2].value]
	= byte_to_int(instr.vm->map, get_address(instr.process->pc
	+ ((instr.params[0].value + instr.params[1].value) % IDX_MOD)), 4);
	return (free_params(instr, 1));
}

int	sti(t_instr instr)
{
	get_params(&instr);
	if (!compare_params(instr.params, instr.opcode)
	|| !valid_reg(--instr.params[0].value)
	|| !convert_params_start(&instr, 1, 3))
		return (free_params(instr, 0));
	int_to_bytes(instr.process->reg[instr.params[0].value],
	get_address(instr.process->pc +
	((instr.params[1].value + instr.params[2].value) % IDX_MOD)),
	instr.vm->map, instr);
	return (free_params(instr, 1));
}

int	core_fork(t_instr instr)
{
	int i;

	i = -1;
	add_process(instr.vm, get_address(instr.process->pc +
	(byte_to_int(instr.vm->map, instr.process->pc + 1, 2) % IDX_MOD)),
	instr.process->reg[1]);
	instr.vm->processes->carry = instr.process->carry;
	instr.vm->processes->alive = instr.process->alive;
	instr.vm->processes->color = instr.process->color;
	while (++i < REG_NUMBER)
		instr.vm->processes->reg[i] = instr.process->reg[i];
	return (decal_pc(instr, 3, 1));
}

int	lld(t_instr instr)
{
	get_params(&instr);
	if (!compare_params(instr.params, instr.opcode)
	|| !valid_reg(--instr.params[1].value))
		return (free_params(instr, 0));
	if (instr.params[0].type == T_DIR)
		instr.process->reg[instr.params[1].value] = instr.params[0].value;
	else
	{
		instr.process->reg[instr.params[1].value]
		= byte_to_int(instr.vm->map,
		get_address(instr.process->pc + instr.params[0].value), 4);
	}
	instr.process->carry = instr.process->reg[instr.params[1].value] == 0;
	return (free_params(instr, 1));
}

int	lldi(t_instr instr)
{
	get_params(&instr);
	if (!compare_params(instr.params, instr.opcode)
	|| !valid_reg(--instr.params[2].value)
	|| !convert_params_unrestrained(&instr, 2))
		return (free_params(instr, 0));
	instr.process->reg[instr.params[2].value]
	= byte_to_int(instr.vm->map, get_address(instr.process->pc
	+ ((instr.params[0].value + instr.params[1].value))), 4);
	instr.process->carry = instr.process->reg[instr.params[2].value] == 0;
	return (free_params(instr, 1));
}

int	core_lfork(t_instr instr)
{
	int i;

	i = -1;
	add_process(instr.vm, get_address(instr.process->pc +
	byte_to_int(instr.vm->map, instr.process->pc + 1, 2)),
	instr.process->reg[1]);
	instr.vm->processes->carry = instr.process->carry;
	instr.vm->processes->alive = instr.process->alive;
	instr.vm->processes->color = instr.process->color;
	while (++i <= REG_NUMBER)
		instr.vm->processes->reg[i] = instr.process->reg[i];
	return (decal_pc(instr, 3, 1));
}

int	aff(t_instr instr)
{
	get_params(&instr);
	if (!compare_params(instr.params, instr.opcode)
	|| !valid_reg(--instr.params[0].value)
	|| !get_champ_by_num(instr.vm->champ, instr.process->reg[1]))
		return (free_params(instr, 0));
	if (!instr.vm->visu)
		ft_printf("{CYAN}AFF:[%d] - %s:%c{EOC}\n", instr.process->reg[1],
		get_champ_by_num(instr.vm->champ, instr.process->reg[1])->name,
		instr.process->reg[instr.params[0].value]);
	return (free_params(instr, 1));
}
