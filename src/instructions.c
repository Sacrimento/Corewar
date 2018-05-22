/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 12:36:15 by mfonteni          #+#    #+#             */
/*   Updated: 2018/05/22 14:50:25 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//fonction qui dechiffre l'encodage des parametres
#include "../include/corewar.h"

int live(t_champ *champ_list, int champ_num, int display_flag)
{
	t_champ *champ;

	if (!champ_list)
		return (0);
	if (!(champ = get_champ_by_num(champ_list, champ_num)))
		return (0);
	champ->lives++;
	he_lives(champ, display_flag);
	return (1);
}

int ld(t_process *process, int value, int *reg)
{
	if (!reg)
		return (process->carry = 0);
	
}