/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 12:09:51 by mfonteni          #+#    #+#             */
/*   Updated: 2018/01/22 15:40:08 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "includes/libft.h"

int		ft_putwstr(wchar_t *s)
{
	int count;
	int ret;

	count = 0;
	ret = 0;
	if (s)
	{
		while (s[count])
			ret += ft_putwchar((wchar_t)s[count++]);
	}
	return (ret);
}

int		ft_putwstrn(wchar_t *s, int n)
{
	int count;
	int ret;

	count = 0;
	ret = 0;
	if (s)
	{
		while (s[count] && count < n)
			ret += ft_putwchar((wchar_t)s[count++]);
	}
	return (ret);
}
