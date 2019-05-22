/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:33:35 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:33:37 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_numlen_base(uintmax_t value, uintmax_t base)
{
	size_t	size;

	size = 0;
	while (value != 0)
	{
		value /= base;
		size++;
	}
	return (size);
}
