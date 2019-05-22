/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:15:42 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/13 15:39:35 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		index_is_special(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_special(str[i]))
			return (i);
		i++;
	}
	return (-1);
}

int		no_id_conv(char *format)
{
	int k;

	k = 0;
	while (format[k])
	{
		if (is_fconv(format[k]))
			return (0);
		k++;
	}
	return (1);
}

void	handle_neg(t_flags *flag)
{
	flag->plus = '-';
	if (!flag->width && flag->space)
		flag->space = 0;
}
