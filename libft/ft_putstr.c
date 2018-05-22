/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 19:16:13 by mfonteni          #+#    #+#             */
/*   Updated: 2018/01/21 18:25:09 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "includes/libft.h"

void	ft_putstr(char const *s)
{
	if (s)
		write(1, s, ft_strlen(s));
}

int		ft_putstrn(char const *s, int n)
{
	int count;

	count = 0;
	if (s)
	{
		while (s[count] && count < n)
			ft_putchar(s[count++]);
	}
	return ((size_t)count < ft_strlen(s) ? count : (int)ft_strlen(s));
}
