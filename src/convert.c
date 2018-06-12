/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/12 15:44:27 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int	byte_to_int(unsigned char *map, int cursor, int amount_of_bytes)
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
/* 	int decal;
	int result;

	ft_printf("{MAGENTA}cursor:%d,bytes:%d{EOC}\n", cursor, amount_of_bytes);
	if (!map)
		return (0);
	decal = -1;
	result = map[cursor % MEM_SIZE] << 8;
	while (++decal < amount_of_bytes)
		result |= map[(cursor + decal) % MEM_SIZE] << 8;
	return (result); */
	int	size;
	int	i;

	i = -1;
	size = 0;
	while (++i < amount_of_bytes)
	{
		size |= map[(cursor + i) % MEM_SIZE];
		size <<= 8;
	}
	return (size >> 8);
}

int get_address(int value)
{
	if (value < 0)
		value = MEM_SIZE + (value % MEM_SIZE);
	return (value % MEM_SIZE);
}

int	int_to_bytes(int n, int cursor, unsigned char *map)
{
	int decal;

	if (!map)
		return (0);
	decal = -1;
	while (++decal < 4)
	{
		map[(cursor + decal) % MEM_SIZE] = (n >> (24 - (decal * 8))) & 0xFF;
		ft_printf("{MAGENTA}int:%d|value:%d|cursor:%d|pos:%d{EOC}\n", n, ((n >> (24 - (decal * 8))) & 0xFF), cursor, cursor + decal);
	}
	return (1);
}

