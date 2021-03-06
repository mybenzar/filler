/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:44:01 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:44:02 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	char	*new;
	int		i;

	i = 0;
	if (s == NULL || !f)
		return (0);
	if (!(new = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (0);
	while (*s != '\0')
	{
		new[i] = (*f)(*s);
		s++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
