/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_params_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/11 18:37:57 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int compare_params(t_param *params, int opcode)
{
	int i;

	i = -1;
	if (!params || --opcode < 0 || opcode > 17)
	{
		INFONUM(opcode);
		ERROR("Compare params : wrong opcode or null params");
		return (0);
	}
	while (++i < 3)
	{
		if ((!g_op_tab[opcode].type_param[i] && params[i].type)
		|| !((params[i].type & g_op_tab[opcode].type_param[i])
		== g_op_tab[opcode].type_param[i]))
			return (0);
	}
	return (1);
}

void convert_params(t_instr instr, int limit)
{
	int i;

	i = -1;
	if (!instr.params)
		return ;
	while (++i < limit)
	{
		if (instr.params[i].type == T_REG)
			instr.params[i].value = instr.process->reg[instr.params[i].value];
		else if (instr.params[i].type == T_IND)
			instr.params[i].value =
			bytetoint(instr.vm->map, get_address((instr.process->pc
			+ (instr.params[i].value % IDX_MOD))), DIR_SIZE);
	}
}

void convert_params_start(t_instr instr, int start, int limit)
{
	int i;

	i = start - 1;
	if (!instr.params)
		return ;
	while (++i < limit)
	{
		if (instr.params[i].type == T_REG)
			instr.params[i].value = instr.process->reg[instr.params[i].value];
		else if (instr.params[i].type == T_IND)
			instr.params[i].value =
			bytetoint(instr.vm->map, get_address((instr.process->pc
			+ (instr.params[i].value % IDX_MOD))), DIR_SIZE);
	}
}

void convert_params_unrestrained(t_instr instr, int limit)
{
	int i;

	i = -1;
	if (!instr.params)
		return ;
	while (++i < limit)
	{
		if (instr.params[i].type == T_REG)
			instr.params[i].value = instr.process->reg[instr.params[i].value];
		else if (instr.params[i].type == T_IND)
			instr.params[i].value =
			bytetoint(instr.vm->map, get_address((instr.process->pc
			+ instr.params[i].value)), DIR_SIZE);
	}
}

int type_to_size(int type)
{
	if (type == T_DIR)
		return (DIR_SIZE);
	else if (type == T_IND)
		return (IND_SIZE);
	else if (type == T_REG)
		return (1);
	return (0);
}