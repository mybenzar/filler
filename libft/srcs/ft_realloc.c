/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:36:34 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:36:51 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	old_size;

	new_ptr = NULL;
	old_size = ft_strlen((const char *)ptr);
	if (!size)
		return (NULL);
	if (!ptr)
	{
		if (!(new_ptr = malloc(size)))
			return (NULL);
		return (new_ptr);
	}
	if (size > old_size)
	{
		if (!(new_ptr = malloc(size)))
			return (NULL);
	}
	if (!(new_ptr = ft_memalloc(size)))
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}
