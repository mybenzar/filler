/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:46:31 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:46:32 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	int		find;

	find = 0;
	i = 0;
	j = 0;
	while (haystack[i] != '\0' && find == 0 && len-- >= ft_strlen(needle))
	{
		find = 1;
		while (haystack[i + j] != '\0' && needle[j] != '\0')
		{
			if (haystack[i + j] != needle[j])
				find = 0;
			j++;
		}
		j = 0;
		i++;
	}
	if (find == 1)
		return ((char *)haystack + i - 1);
	return (0);
}
