/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:07:29 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/19 15:10:29 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	display_board(t_board *board)
{
	int i;

	i = 0;
	while (i < board->height)
		ft_printf("%s\n", board->tab[i++]);
}

void	display_piece(t_board *board)
{
	int i;

	i = 0;
	ft_printf("board->piece->size = %d\n", board->piece->size);
	while (i < board->piece->size)
	{
		ft_printf("board->piece->pos[%d].x = %d // board->piece->pos[%d].y = %d\n", i, board->piece->pos[i].x, i, board->piece->pos[i].y);
		i++;
	}
	ft_printf("board->piece->height = %d\n", board->piece->height);
	ft_printf("board->piece->width = %d\n", board->piece->width);
}
