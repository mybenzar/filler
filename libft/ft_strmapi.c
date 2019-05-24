/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:44:17 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:44:18 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*new;
	unsigned int	i;

	if (s == NULL || !f)
		return (0);
	if (!(new = (char *)malloc(sizeof(char) * ft_strlen(s) + 1)))
		return (0);
	i = 0;
	while (*s != '\0')
	{
		new[i] = (*f)(i, *s);
		s++;
		i++;
	}
	new[i] = '\0';
	return (new);
}
