/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_params_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/06/05 12:55:03 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

/* int count_params(t_param *params)
{
	if (params)
		return (params[0].type != 0
		+ params[1].type != 0
		+ params[2].type != 0);
	return (0);
} */

int compare_params(t_param *params, int opcode)
{
	if (params && --opcode >= 0)
		return ((params[0].type & g_op_tab[opcode].type_param[0])
		== g_op_tab[opcode].type_param[0]
		&& (params[0].type & g_op_tab[opcode].type_param[1])
		== g_op_tab[opcode].type_param[1]
		&& (params[0].type & g_op_tab[opcode].type_param[0])
		== g_op_tab[opcode].type_param[0]);
	return (0);
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
			instr.params[i].value = bytetoint(&instr.vm->map[instr.process->pc
			+ (instr.params[i].value % IDX_MOD)], 4);
	}
}

int convert_params_unrestrained(t_instr instr, int limit)
{
	int i;

	i = -1;
	if (!instr.params)
		return (0);
	while (++i < limit)
	{
		if (instr.params[i].type == T_REG)
			instr.params[i].value = instr.process->reg[instr.params[i].value];
		else if (instr.params[i].type == T_IND)
			instr.params[i].value = bytetoint(&instr.vm->map[instr.process->pc
			+ (instr.params[i].value % IDX_MOD)], 4);
	}
	return (1);
}