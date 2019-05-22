/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:31:18 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/15 11:31:19 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstswap_content(t_list *lst_a, t_list *lst_b)
{
	void	*tmp_content;
	size_t	tmp_size;

	tmp_content = ft_memalloc(lst_a->content_size);
	ft_memcpy(tmp_content, lst_a->content, lst_a->content_size);
	tmp_size = lst_a->content_size;
	ft_memcpy(lst_a->content, lst_b->content, lst_b->content_size);
	lst_a->content_size = lst_b->content_size;
	ft_memcpy(lst_b->content, tmp_content, tmp_size);
	lst_b->content_size = tmp_size;
}
