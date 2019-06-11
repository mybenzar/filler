/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:48:11 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:48:14 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char		*ft_strtrim(char const *s)
{
	char			*s_trim;
	unsigned int	begin_ws;
	unsigned int	end_ws;
	int				j;

	if (s == NULL)
		return (NULL);
	begin_ws = 0;
	end_ws = 0;
	while (is_whitespace(s[begin_ws]) && begin_ws < ft_strlen(s))
		begin_ws++;
	j = ft_strlen(s) - 1;
	while (is_whitespace(s[j]) && j-- >= 0)
		end_ws++;
	if (begin_ws == ft_strlen(s))
		return (ft_strdup(""));
	if (!(s_trim = ft_strsub(s, begin_ws, ft_strlen(s) - (begin_ws + end_ws))))
		return (NULL);
	return (s_trim);
}
