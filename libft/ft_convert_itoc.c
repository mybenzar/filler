/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_itoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:26:35 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:26:37 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_convert_itoc(uintmax_t value)
{
	char	*base_ref;

	base_ref = "0123456789abcdef";
	return (base_ref[value]);
}
