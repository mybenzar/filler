/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:32:41 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:32:43 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void const *src, size_t len)
{
	char		*p_dest;
	char const	*p_src;

	if (dest == src)
		return (dest);
	if (dest < src)
	{
		p_dest = (char *)dest;
		p_src = (char const *)src;
		while (len--)
			*(p_dest)++ = *(p_src)++;
	}
	else
	{
		p_dest = (char *)dest + (len - 1);
		p_src = (char const *)src + (len - 1);
		while (len--)
			*p_dest-- = *p_src--;
	}
	return (dest);
}
