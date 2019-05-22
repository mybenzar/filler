/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:47:40 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:47:40 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;
	int find;

	find = 0;
	i = 0;
	j = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] != '\0' && find == 0)
	{
		find = 1;
		while (needle[j] != '\0')
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
	return (NULL);
}
