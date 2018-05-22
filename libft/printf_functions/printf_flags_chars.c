/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_flags_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfonteni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 12:40:51 by mfonteni          #+#    #+#             */
/*   Updated: 2018/01/22 18:52:44 by mfonteni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	writespaces(int spaces)
{
	int		count;

	count = 0;
	if (spaces > 0)
	{
		while (count++ < spaces)
			ft_putchar(' ');
	}
	return (spaces);
}

static int	goodstrlen(t_plist *list)
{
	intmax_t	c;

	c = 0;
	if (list->type == 'S' || (list->type == 's' && check_lconv(list)))
		return ((int)ft_wstrlen(list->arg));
	if (list->type == 's' && !check_lconv(list))
		return ((int)ft_strlen(list->arg));
	if (list->type == 'c' && !check_lconv(list))
		return (1);
	if (list->type == 'C' || (list->type == 'c' && check_lconv(list)))
	{
		c = (intmax_t)list->arg;
		return (ft_getbyteslength(c));
	}
	return (0);
}

int			printf_flags_chars(t_plist *list)
{
	int written;
	int towrite;

	written = 0;
	towrite = (list->precision > -1 && goodstrlen(list) > list->precision
			? list->precision : goodstrlen(list));
	if (list->arg == NULL && (list->type == 's' || list->type == 'S')
			&& list->precision == -1)
		return (ft_putstrn("(null)", 6));
	if (!ft_strchr(list->flag, '-') && towrite < list->width)
		written += writespaces(list->width - towrite);
	if (list->precision > -1 && list->precision < goodstrlen(list))
		written += (list->type == 's' && !check_lconv(list) ?
				ft_putstrn(list->arg, list->precision) :
				ft_putwstrn((wchar_t*)list->arg, list->precision));
	else if (list->type == 's' && !check_lconv(list))
	{
		ft_putstr(list->arg);
		written += goodstrlen(list);
	}
	else
		written += ft_putwstr((wchar_t*)list->arg);
	if (ft_strchr(list->flag, '-') && towrite < list->width)
		written += writespaces(list->width - towrite);
	return (written);
}

int			printf_flags_char(t_plist *list)
{
	int			written;
	intmax_t	arg;

	arg = (intmax_t)list->arg;
	written = 0;
	if (!ft_strchr(list->flag, '-') && 1 < (size_t)list->width)
		written += writespaces((size_t)list->width - 1);
	if (list->type == 'c' && !check_lconv(list))
	{
		ft_putchar(arg);
		written += 1;
	}
	else
		written += ft_putwchar(arg);
	if (ft_strchr(list->flag, '-') && 1 < (size_t)list->width)
		written += writespaces((size_t)list->width - 1);
	return (written);
}
