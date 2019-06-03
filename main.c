/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 15:21:14 by mybenzar          #+#    #+#             */
/*   Updated: 2019/05/24 19:36:42 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int	main(void)
{
	t_board	*board;
	int		p_id;

	if (!(board = (t_board*)malloc(sizeof(t_board))))
		return (0);
	p_id = get_player();
	ft_printf("p_id = %d\n", p_id);
	allocate_board(board);
	get_board(board);
	display_board(board);
	free_board(board);
	return (0);
}
