/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:29:34 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:29:36 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *tmp;
	t_list *stock;

	if (alst == NULL)
		return ;
	tmp = *alst;
	while (tmp)
	{
		stock = tmp;
		tmp = tmp->next;
		(*del)(stock->content, stock->content_size);
		free(stock);
	}
	*alst = NULL;
}
