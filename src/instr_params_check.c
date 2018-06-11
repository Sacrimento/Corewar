/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instr_params_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2018/06/08 13:19:33 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/08 14:44:12 by mfonteni         ###   ########.fr       */
=======
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2018/06/10 14:59:03 by abouvero         ###   ########.fr       */
>>>>>>> e9258c57b21166fd3cb4ea079a78a97862e229a8
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

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
			instr.params[i].value =
			bytetoint(instr.vm->map, get_address((instr.process->pc
			+ (instr.params[i].value % IDX_MOD))), T_DIR);
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
			+ (instr.params[i].value % IDX_MOD))), T_DIR);
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
			+ instr.params[i].value)), T_DIR);
	}
}
