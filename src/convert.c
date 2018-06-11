/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <mfonteni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:40:13 by mfonteni          #+#    #+#             */
/*   Updated: 2018/06/11 15:12:33 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

int	bytetoint(unsigned char *map, int cursor, int amount_of_bytes)
{
	int decal;
	int result;

	if (!map)
		return (0);
	decal = (amount_of_bytes - 1) * 8;
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
	return (1);
}
