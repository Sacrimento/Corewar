/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_loaders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 15:10:02 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/26 15:53:26 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

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
	instr.process->carry = instr.process->reg[instr.params[1].value] == 0;
	return (free_params(instr, 1));
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

int	ldi(t_instr instr)
{
	get_params(&instr);
	if (!compare_params(instr.params, instr.opcode)
	|| !valid_reg(--instr.params[2].value)
	|| !convert_params(&instr, 2))
		return (free_params(instr, 0));
	instr.process->reg[instr.params[2].value]
	= byte_to_int(instr.vm->map, get_address(instr.process->pc
	+ ((instr.params[0].value + instr.params[1].value) % IDX_MOD)), 4);
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
