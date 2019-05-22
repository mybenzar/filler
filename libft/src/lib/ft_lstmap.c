/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:30:08 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:30:11 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *tmp;
	t_list *temp1;

	new = NULL;
	while (lst)
	{
		temp1 = f(lst);
		if (new == NULL)
		{
			new = temp1;
			tmp = new;
			new->next = NULL;
		}
		else
		{
			new->next = temp1;
			new = new->next;
		}
		lst = lst->next;
	}
	return (tmp);
}
