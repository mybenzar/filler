/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:31:47 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:31:48 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	while (n--)
	{
		*(unsigned char *)dest = *(unsigned const char *)src;
		if (*(unsigned const char *)src == (unsigned char)c)
		{
			dest++;
			return (dest);
		}
		src++;
		dest++;
	}
	return (NULL);
}
