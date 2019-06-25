/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mybenzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 19:07:29 by mybenzar          #+#    #+#             */
/*   Updated: 2019/06/25 16:03:00 by mybenzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	display_board(t_board *board)
{
	int i;

	i = 0;
	dprintf(2, "board->height = %d, board->width = %d\n", board->height, board->width);
	while (i < board->height)
		dprintf(2, "%s\n", board->tab[i++]);
}

void	display_piece(t_piece *piece)
{
	int i;

	i = 0;
	dprintf(2, "board->piece->size = %d\n", piece->size);
	while (i < piece->size)
	{
		dprintf(2, "piece->pos[%d].x = %d // piece->pos[%d].y = %d\n", i, piece->pos[i].x, i, piece->pos[i].y);
		i++;
	}
	dprintf(2, "board->piece->height = %d\n", piece->height);
	dprintf(2, "board->piece->width = %d\n", piece->width);
}
