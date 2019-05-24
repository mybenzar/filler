/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:43:24 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:43:27 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char const *src, size_t size)
{
	size_t i;
	size_t j;
	size_t final_size;

	i = (size_t)ft_strlen(dest);
	j = (size_t)ft_strlen(src);
	dest += i;
	if (size <= i)
		return (j + size);
	final_size = size - i - 1;
	while (final_size > 0 && *src)
	{
		*dest++ = *src++;
		final_size--;
	}
	*dest = '\0';
	return (i + j);
}
