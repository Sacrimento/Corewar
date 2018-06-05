/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/05 14:40:12 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

unsigned int	bytetoint(unsigned char *map, int ammount_of_bytes)
{
	if (!map)
		return (0);
	if (ammount_of_bytes == T_REG)
		return (map[0]);
	if (ammount_of_bytes == T_IND)
		return (map[0] | (map[1] << 8));
	if (ammount_of_bytes == T_DIR)
		return ((map[0] << 24) | (map[1] << 16) | (map[2] << 8) | map[3]);
	return (0);
}

int	inttobytes(unsigned int n, unsigned char *map)
{
	if (!map)
		return (0);
	map[0] = (n >> 24) & 0xFF;
	map[1] = (n >> 16) & 0xFF;
	map[2] = (n >> 8) & 0xFF;
	map[3] = n & 0xFF;
	return (1);
}
