/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_checks2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:53:28 by mfonteni          #+#    #+#             */
/*   Updated: 2018/01/21 12:32:44 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_signed(char c)
{
	if (c == 'd' || c == 'i' || c == 'D')
		return (1);
	return (0);
}

int	is_octal_or_hex(char c)
{
	if (c == 'x' || c == 'X' || c == 'o' || c == 'p')
		return (1);
	return (0);
}