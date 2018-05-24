/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:36:15 by mfonteni          #+#    #+#             */
/*   Updated: 2018/05/24 16:08:40 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO: fonction qui dechiffre l'encodage des parametres
#include "../include/corewar.h"

int live(t_champ *champ_list, int champ_num, t_vm *vm)
{
	t_champ *champ;

	if (!champ_list || !(champ = get_champ_by_num(champ_list, champ_num)))
		return (0);
	champ->lives++;
	he_lives(champ, vm);
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