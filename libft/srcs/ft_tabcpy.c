/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 15:23:29 by mybenzar          #+#    #+#             */
/*   Updated: 2019/07/04 15:24:12 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_tabcpy(char **tab)
{
	int		i;
	char	**ret;

	i = 0;
	while (tab[i] != NULL)
		i++;
	if (!(ret = (char **)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = -1;
	while (tab[++i] != NULL)
	{
		if (!(ret[i] = ft_strdup(tab[i])))
			return (NULL);
	}
	ret[i] = NULL;
	return (ret);
}
