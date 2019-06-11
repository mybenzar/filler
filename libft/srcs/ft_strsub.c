/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:47:53 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:47:56 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str_sub;
	size_t	len_max;
	size_t	i;

	if (s == NULL)
		return (NULL);
	len_max = (ft_strlen(s) - start);
	if (len <= len_max)
	{
		if (!(str_sub = (char *)malloc(sizeof(char) * len + 1)))
			return (NULL);
		i = 0;
		while (i < len)
		{
			str_sub[i] = s[start + i];
			i++;
		}
		str_sub[i] = '\0';
		return (str_sub);
	}
	return (0);
}
