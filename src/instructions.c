/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:36:15 by mfonteni          #+#    #+#             */
/*   Updated: 2018/05/28 15:25:21 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//si c'est un registre c'est 1 octet direct ca doit etre 2 et ind 4
//TODO: fonction qui dechiffre l'encodage des parametres
#include "../include/corewar.h"

int		decode_OCP(t_instr *instr, t_vm *vm, unsigned char byte)
{
	int i;

	i = 0;
	ft_bzero(instr->params, sizeof(t_instr) * 3);
	while (++i < 4)
	{
		if ((byte >> (i * 2)) & 0x0000000F)
		{
			//register
			if (instr->process->pc + i > REG_SIZE)
				return (0);
			instr->params[i].value = instr->process->reg[vm->map[instr->process->pc + i]];
			instr->params[i].address = &instr->process->reg[vm->map[instr->process->pc + i]];
			instr->params[i].active = 1;
		}
		else if ((byte >> (i * 2)) & 0x000000F0)
		{
			//direct
			instr->params[i].value = vm->map[instr->process->pc + i];
			instr->params[i].address = &vm->map[instr->process->pc + i];
			instr->params[i].active = 1;
		}
		else if ((byte >> (i * 2)) & 0x000000FF)
		{
			//indir
			instr->param.indir[i] = 1;
		}
			
	}
	return (1);
}

int live(t_instr instr, t_champ *champions, t_vm *vm)
{
	t_champ *thischamp;

	if (!vm || !champions
	|| !(thischamp = get_champ_by_num(champions, champ_num)))
		return (0);
	thischamp->lives++;
	if (vm->display_live)
		ft_printf("[%d]{BLUE}Champion %s(id:%d) is alive{EOC}",
		thischamp->lives, thischamp->name, thischamp->id);
	return (1);
}
//not sure about this one :
int ld(t_process *process, int value, int *reg)
{
	if (!reg)
		return (process->carry = 0);
	*reg = value;
	return (process->carry = 1);
}

int lld()
{
	
}

int st(t_process *process, int *reg1, int *reg2)
{
	if (!reg1 || !reg2)
		return (process->carry = 0);
	*reg2 = *reg1;
	return (process->carry = 1);
}

int sti()
{

}

int zjmp(t_process *process, unsigned char *addr)
{
	if (!process || process->carry == 0)
		return (0);
}
// prend 2 index et 1 registre, additionne les 2 premiers, 
// traite ca comme une adresse, y lit une valeur de la taille d’un 
// registre et la met dans le 3eme.
int ldi()
{

}

int lldi()
{
	
}

int aff(int *reg)
{
	if (!reg)
		return (0);
	ft_putchar(*reg % 256);
	return (1);
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