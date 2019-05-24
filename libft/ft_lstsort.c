/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:31:01 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:31:03 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstsort(t_list *lst, int (*cmp)(int, int))
{
	t_list	*tmp;
	t_list	*tmp2;
	int		sort_kind;

	sort_kind = 0;
	if (!lst)
		return (NULL);
	tmp = lst;
	if ((sort_kind = (*cmp)((int)tmp->content, (int)(tmp->next)->content) == 0))
		sort_kind = 1;
	else
		sort_kind = (*cmp)((int)tmp->content, (int)(tmp->next)->content);
	while (tmp->next)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if ((*cmp)((int)tmp->content, (int)tmp2->content) != sort_kind)
				ft_lstswap_content(tmp, tmp2);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	return (lst);
}
