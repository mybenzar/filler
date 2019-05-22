/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:42:52 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:42:55 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_join;
	char	*tmp;
	size_t	sjoin_size;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	sjoin_size = ft_strlen(s1) + ft_strlen(s2);
	if (!(s_join = (char *)malloc(sizeof(char) * sjoin_size + 1)))
		return (NULL);
	tmp = ft_strdup(s1);
	s_join = ft_strcat(tmp, s2);
	return (s_join);
}
