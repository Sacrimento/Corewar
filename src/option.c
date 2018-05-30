/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouvero <abouvero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 17:17:57 by abouvero          #+#    #+#             */
/*   Updated: 2018/05/30 19:34:05 by abouvero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/corewar.h"

static int	incorrect_arg(char *opt, char *str, int err)
{
	ft_printf("%s", opt);
	ft_printf(" %s : incorrect argument ", str);
	if (err == 1)
		ft_printf("(must be between 1 and 2147483647)\n");
	else if (err == 2)
		ft_printf("(must contain digits only)\n");
	return (-1);
}

static int	ft_satoi(char *str, char *opt)
{
	int			i;
	long long	final;

	i = 0;
	final = 0;
	if (str[i] == '-' && ft_isdigit(str[i + 1]))
		return (incorrect_arg(opt, str, 1));
	if (!ft_isdigit(str[i]))
		return (incorrect_arg(opt, str, 2));
	while (ft_isdigit(str[i]))
		if ((final = (final * 10) + (str[i++] - 48)) > 2147483647)
			return (incorrect_arg(opt, str, 1));
	if (str[i])
		return (incorrect_arg(opt, str, 2));
	return (!final ? incorrect_arg(opt, str, 1) : (int)final);
}

int			known_opt(char *opt)
{
	if (!ft_strcmp(opt, "-n") || !ft_strcmp(opt, "-dump"))
		return (1);
	return (0);
}

int			is_opt(char *opt, char *nbr, t_vm *vm, int *ch_num)
{
	int		num;

	if (!nbr)
	{
		ft_printf("%s : missing argument\n", opt);
		return (usage(-1));
	}
	if ((num = ft_satoi(nbr, opt)) == -1)
		return (-1);
	if (!ft_strcmp(opt, "-n"))
		*ch_num = num;
	else
		vm->dump = num;
	return (1);
}