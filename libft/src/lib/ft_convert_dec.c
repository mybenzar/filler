/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_dec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:26:24 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:26:25 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_convert_dec(char c, int base)
{
	char	*base_up;
	char	*base_low;
	int		index;

	index = 0;
	base_up = "0123456789ABCDEF";
	base_low = "0123456789abcdef";
	while (base_up[index] != '\0' && index <= base)
	{
		if (base_up[index] == c || base_low[index] == c)
			return (index);
		index++;
	}
	return (0);
}
