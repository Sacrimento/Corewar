/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/07 17:55:12 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int	bytetoint(unsigned char *map, int cursor, int ammount_of_bytes)
{
/* OLD
	if (!map)
		return (0);
	if (ammount_of_bytes == T_REG)
		return (map[0]);
	if (ammount_of_bytes == T_IND)
		return (map[0] | (map[1] << 8));
	if (ammount_of_bytes == T_DIR)
		return ((map[0] << 24) | (map[1] << 16) | (map[2] << 8) | map[3]);
*/
	int decal;
	int result;

	decal = (ammount_of_bytes - 1) * 8;
	result = map[cursor % MEM_SIZE] << decal;
	while ((decal = decal - 8) >= 0)
		result = result | map[cursor++ % MEM_SIZE] << decal;
	return (result);
}

int get_address(int value)
{
	if (value < 0)
		value = MEM_SIZE + (value % MEM_SIZE);
	return (value % MEM_SIZE);
}

int	inttobytes(int n, int cursor, unsigned char *map)
{
	int decal;

	if (!map)
		return (0);
	decal = -1;
	while (++decal < 4)
		map[(cursor + decal) % MEM_SIZE] = (n >> (24 - (decal * 8))) & 0xFF;
/* 	map[cursor % MEM_SIZE] = (n >> 24) & 0xFF;
	map[(cursor + 1) % MEM_SIZE] = (n >> 16) & 0xFF;
	map[(cursor + 2) % MEM_SIZE] = (n >> 8) & 0xFF;
	map[(cursor + 3) % MEM_SIZE] = n & 0xFF; */
	return (1);
}
